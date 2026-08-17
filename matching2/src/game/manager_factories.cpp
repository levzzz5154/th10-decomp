#include "th10/game/manager_factories.hpp"
#include "th10/game/gameplay_final_runtime.hpp"
#include "th10/game/entity.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/pool_constructors.hpp"
#include "th10/render/anm_vm_draw_dispatch.hpp"
#include "th10/render/recovered_render_leaves.hpp"
#include "th10/runtime/missing_edge.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

extern Entity* __fastcall Entity_Constructor(Entity* entity);
extern unsigned int DAT_004776f4;
extern unsigned int DAT_00477834;  // player position (the 0x0041AFD0 sweep)
extern float DAT_00476f78;          // frame delta (the 0x0041AFD0 sweep)
extern unsigned int DAT_0047770c;
extern unsigned int DAT_00491be4;

// Retail globals feeding the recovered particle/effect draw pass.


namespace {
ParticleEffectRuntimeBindings g_particle_effect_bindings = {};

int __fastcall ParticleEffect_Update(void* owner) {
	// 0x0041AFD0 (the item sweep) is reconstructed as UpdateItems
	// (gameplay_final_runtime); the owner is the item pool and the env
	// reads the player position + the collect/magnet rects from the
	// player record (dword_477834 +960/+964 and slots 4297-4314).
	th10::gameplay_final::ItemEnv env;
	if (DAT_00477834 != 0) {
		const float* pos = (const float*)(uintptr_t)DAT_00477834;
		env.player_x = *(pos + 240);
		env.player_y = *(pos + 241);
		env.collect_l = *(pos + 4297); env.collect_t = *(pos + 4298);
		env.collect_r = *(pos + 4299); env.collect_b = *(pos + 4300);
		env.magnet_l = *(pos + 4309);  env.magnet_t = *(pos + 4310);
		env.magnet_r = *(pos + 4311);  env.magnet_b = *(pos + 4312);
	}
	env.frame_delta = DAT_00476f78;
	return UpdateItems(*(th10::gameplay_final::ItemPool*)owner, env);
}

// Retail 0x0041B8E0 reads the shared effect bank through the
// animation-manager resource slot (dword_4776F0 + 1016532 dwords =
// +0x3E0B50 bytes) for the per-record glyph-bank preloads.
void* ParticleEffect_Bank() {
	return 0;  // retail dword_4776F0 is hybrid-only; host injects its
	           // own resource bindings over this path
}

// Retail 0x0041B8E0 draws the 2198 effect records: the pool slots start
// at +0x14 with a 0x3F0 stride and the record payload sits at +0x34C.
// Each live record (dword at +164) is projected from its unprojected
// triple (+116/+120/+124, biased by +224.0/+16.0), records entering
// below y=8.0 are faded through the alpha byte at -57, the glyph bank
// is preloaded (retail 0x0043E5A0) when the record's slot id (int16 at
// +76) no longer matches the current bank + 344/353, and the record is
// emitted through the shared sub_4451C0 draw dispatch on the record's
// ANM VM at the slot base.
int __fastcall ParticleEffect_Draw(void* owner) {
	// The host draw binding is superseded by the recovered pass; the
	// retail globals feed the draw environment directly.
	Byte* slot = (Byte*)owner + 20;
	Byte* record = (Byte*)owner + 844;
	static AnmDrawEnv env = th10::render_leaves::DefaultAnmDrawEnv();
	void* context = 0;  // host injects its own draw binding over this path
	for (int count = 2198; count != 0; --count) {
		if (*(Word*)(record + 164) != 0) {
			*(float*)(record - 4) = *(float*)(record + 116) + 224.0f;
			*(float*)record = *(float*)(record + 120) + 16.0f;
			*(Word*)(record + 4) = *(Word*)(record + 124);
			if (*(float*)record >= 8.0f) {
				const int bank = *(int*)(record + 172);
				if (*(short*)(record + 76) != bank + 344) {
					void* resource_bank = ParticleEffect_Bank();
					if (resource_bank != 0)
						EffectRuntime_Preload(slot, bank + 343, resource_bank);
					*(Byte*)(record - 57) = 0xFF;
				}
			} else {
				const double previous_y = *(float*)record;
				*(float*)record = 25.0f;  // retail store 1103101952
				const double fade = previous_y - 8.0;
				if (fade < 32.0)
					*(Byte*)(record - 57) = (Byte)(unsigned long long)(
					    fade * 0.03125 * 255.0);
				else
					*(Byte*)(record - 57) = 0xFF;
				const int bank = *(int*)(record + 172);
				if (*(short*)(record + 76) != bank + 353) {
					void* resource_bank = ParticleEffect_Bank();
					if (resource_bank != 0)
						EffectRuntime_Preload(slot, bank + 352, resource_bank);
				}
			}
			AnmVm_DrawDispatch((AnmDrawVm*)slot, context, &env);
		}
		slot += 1008;
		record += 1008;
	}
	return 1;
}
}  // namespace

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// Shared construct-then-initialize factory frame used by the manager
// creation helpers: allocate, run the in-place constructor, then run the
// global initializer; a failing initializer tears the object back down.

static void* CreateConstructedManager(unsigned int size,
                                      void* (*allocate)(unsigned int),
                                      void* (*construct)(void*),
                                      int (*initialize)(void),
                                      void (*destroy)(void*),
                                      void (*free_memory)(void*)) {
	void* manager = allocate(size);
	if (manager != 0) manager = construct(manager);
	if (initialize() != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}

// 0x0040D6B0 - Construct the enemy manager. Retail allocates the 0x68-byte
// block, zeroes all 0x1A dwords, sets header flag bit 1, publishes the
// instance through the manager global (retail DAT_00477704), then runs the
// script initializer; on failure the half-built manager is destroyed and
// freed and the constructor reports null.
void* EnemyManager_Create(void* script_name, void* (*allocate)(unsigned int size),
                          void** global_slot,
                          int (*initialize)(void* script_name),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory)) {
    Word* manager = (Word*)allocate(0x68);
    if (manager != 0) {
        for (int index = 0; index < 0x1A; ++index) manager[index] = 0;
        manager[0] = manager[0] | 2;
        *global_slot = manager;
    }
    if (initialize(script_name) != 0) {
        if (manager != 0) {
            if (destroy != 0) destroy(manager);
            free_memory(manager);
        }
        return 0;
    }
    return manager;
}

// 0x0043C8B0 - Construct the 0x44-byte overlay text manager. Retail zeroes
// all 0x11 dwords, sets header flag bit 1, and forwards the five creation
// arguments to the initializer (retail 0x0043C970) before returning the
// instance; allocation failure reports null.

void* AsciiManager_Create(void* (*allocate)(unsigned int size),
                          void (*initialize)(void* manager)) {
    Word* manager = (Word*)allocate(0x44);
    if (manager == 0) return 0;
    for (int index = 0; index < 0x11; ++index) manager[index] = 0;
    manager[0] = manager[0] | 2;
    if (initialize != 0) initialize(manager);
    return manager;
}

// Semantic reconstruction 0x0043C970 - initialize an ASCII overlay manager.
int AsciiManager_Initialize(AsciiManagerInitState* state, void* draw_queue,
                            int mode, int argument_4, int argument_5,
                            int argument_6, int argument_7,
                            const AsciiManagerInitHooks* hooks) {
    static const int update_kinds[9] = {
        kAsciiUpdateBasic, kAsciiUpdateMode1, kAsciiUpdateMode2,
        kAsciiUpdateBasic, kAsciiUpdateMode4, kAsciiUpdateMode2,
        kAsciiUpdateMode6, kAsciiUpdateMode6, kAsciiUpdateMode8,
    };
    static const int draw_kinds[9] = {
        kAsciiDrawMode0, -1, kAsciiDrawMode2, kAsciiDrawMode2,
        kAsciiDrawMode4, kAsciiDrawMode0, kAsciiDrawMode6,
        kAsciiDrawMode7, -1,
    };
    if (mode < 0 || mode > 8)
        return -1;
    if (mode == 3)
        state->color = 255;
    state->update_task = hooks->create_update(
        hooks->context, update_kinds[mode], 14, state);
    if (draw_kinds[mode] >= 0)
        state->draw_task = hooks->create_draw(
            hooks->context, draw_kinds[mode], draw_queue, state);
    hooks->set_finish_callback(hooks->context, state->update_task);

    if ((state->timer_flags & 1u) == 0) {
        state->timer_current = 0;
        state->timer_target = static_cast<int>(0xFFF0BDC1u);
        state->timer_previous = 0;
        state->timer_speed = hooks->frame_speed;
        state->timer_flags |= 1u;
    }
    state->timer_current = 0;
    state->timer_previous = 0;
    state->timer_target = -1;
    state->argument_4 = argument_4;
    state->mode = mode;
    state->argument_5 = argument_5;
    state->argument_6 = argument_6;
    state->argument_7 = argument_7;
    return argument_6;
}

// 0x004296F0 - Construct the 0x2D4-byte stage manager under an SEH frame.
// Retail vector-constructs the eight 0x24-byte interpolator slots at +0xA0,
// zeroes the whole 0xB5-dword block, arms the state word (+0x10) with 2, and
// runs the stage-script initializer; on failure the manager is destroyed and
// freed and the constructor reports null.

void* StageManager_Create(const char* stage_path,
                          void* (*allocate)(unsigned int size),
                          void (*construct_slots)(void* slots, int stride,
                                                  int count),
                          int (*initialize)(void* manager,
                                            const char* stage_path),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory)) {
    Word* manager = (Word*)allocate(0x2D4);
    if (manager != 0) {
        if (construct_slots != 0) construct_slots(manager + 0x28, 0x24, 8);
        for (int index = 0; index < 0xB5; ++index) manager[index] = 0;
    }
    if (manager == 0) return 0;
    manager[4] = 2;
    if (initialize(manager, stage_path) == 0) return manager;
    if (destroy != 0) destroy(manager);
    free_memory(manager);
    return 0;
}

// 0x0042AE60 - Initialize the effect manager pools. Retail zeroes the whole
// 0x772D-dword block, loads the shared effect table into the first slot,
// initializes the trailing shared block (+0x1D86C), constructs the seven
// 0x437C-byte effect pools that start at +0x08, and finishes with the
// archive-section finalizer.

void EffectManager_InitializePools(Word* manager_words,
                                   unsigned int word_count,
                                   const Byte* (*load_effect_table)(
                                       unsigned int* size_out),
                                   const Byte** table_slot,
                                   void (*initialize_shared)(void* shared_block),
                                   void* shared_block,
                                   void (*initialize_pool)(void* pool),
                                   Byte* first_pool,
                                   unsigned int pool_stride,
                                   unsigned int pool_count,
                                   void (*finalize)(void)) {
    for (unsigned int index = 0; index < word_count; ++index) {
        manager_words[index] = 0;
    }
    unsigned int table_size = 0;
    *table_slot = load_effect_table(&table_size);
    if (initialize_shared != 0) initialize_shared(shared_block);
    Byte* pool = first_pool;
    for (unsigned int index = 0; index < pool_count; ++index) {
        initialize_pool(pool);
        pool = pool + pool_stride;
    }
    if (finalize != 0) finalize();
}

// --- Scheduler registration leaves ----------------------------------------------

// Shared body of the registration leaves: create a scheduler node for the
// callback, bind the owner, clear node-flag bit 1 (the auto-release bit),
// and push the node onto the requested queue.
SchedulerCallbackNode* Scheduler_RegisterOwnedCallback(
    void* owner, void* callback,
    SchedulerCallbackNode* (*create)(void* callback),
    void (*enqueue)(void* queue), void* queue) {
    SchedulerCallbackNode* node = create(callback);
    node->owner = owner;
    node->flags = node->flags & 0xFFFFFFFDu;
    if (enqueue != 0) enqueue(queue);
    return node;
}

// 0x0042B4D0 - Effect manager registration hook. Retail stamps the manager
// with the game thread's frame counter (+0x8994), registers the update and
// draw callbacks (both with the auto-release bit cleared) on the shared
// scheduler queue, resets the manager's timer block (+0x18, retail
// 0x00401DE0), stores the stamp copy at +0x320, and preloads the effect
// bank for it (retail 0x0043E5A0 with argument 0xC4).
int EffectManager_OnRegister(ManagerRegistration* manager, int frame_stamp,
                             void* update_callback, void* draw_callback,
                             SchedulerCallbackNode* (*create)(void* callback),
                             void (*enqueue_update)(void* queue),
                             void (*enqueue_draw)(void* queue), void* queue,
                             void (*reset_timer)(void* timer_block),
                             void* timer_block,
                             void (*preload)(int frame_stamp, int argument)) {
    manager->frame_stamp = frame_stamp;
    manager->update = Scheduler_RegisterOwnedCallback(
        manager, update_callback, create, enqueue_update, queue);
    manager->draw = Scheduler_RegisterOwnedCallback(
        manager, draw_callback, create, enqueue_draw, queue);
    int stamp = manager->frame_stamp;
    if (reset_timer != 0) reset_timer(timer_block);
    manager->stored_stamp = stamp;
    if (preload != 0) preload(stamp, 0xC4);
    return 0;
}

void ParticleEffectRuntime_SetBindings(
        const ParticleEffectRuntimeBindings* bindings) {
	if (bindings != 0)
		g_particle_effect_bindings = *bindings;
	else
		std::memset(&g_particle_effect_bindings, 0,
		            sizeof(g_particle_effect_bindings));
}

// 0x0041ADA0 - Install the particle/effect pool's update and draw callbacks.
int ParticleEffectRuntime_Initialize(void* manager) {
	if (manager == 0 || DAT_00491be4 == 0)
		return -1;
	Byte* bytes = (Byte*)manager;
	SchedulerCallback* update =
	    SchedulerCallback_Create(ParticleEffect_Update);
	if (update == 0)
		return -1;
	update->flags &= ~2u;
	update->owner = manager;
	Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
	*(SchedulerCallback**)(bytes + 8) = update;

	SchedulerCallback* draw =
	    SchedulerCallback_Create(ParticleEffect_Draw);
	if (draw == 0) {
		Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
		*(SchedulerCallback**)(bytes + 8) = 0;
		return -1;
	}
	draw->flags &= ~2u;
	draw->owner = manager;
	Scheduler_RegisterSecondary(draw, 0, (void*)(uintptr_t)DAT_00491be4);
	*(SchedulerCallback**)(bytes + 12) = draw;
	return 0;
}

// 0x00408C90 - Player manager factory: 0x37B0-byte object, in-place
// constructor, then the resource initializer; failure destroys and frees.

// 0x00408910 - Construct the 15 embedded entity records. Retail subsequently
// clears the complete object, sets its live bit, and publishes it. Calling the
// entity constructors preserves their construction-time behavior even though
// all of their field stores are deliberately erased by the following clear.

void* PlayerManager_Construct(void* memory) {
	Byte* bytes = (Byte*)memory;
	for (int index = 0; index != 2; ++index)
		Entity_Constructor((Entity*)(bytes + 0x10 + index * 0x3AC));
	for (int index = 0; index != 8; ++index)
		Entity_Constructor((Entity*)(bytes + 0x778 + index * 0x3AC));
	for (int index = 0; index != 5; ++index)
		Entity_Constructor((Entity*)(bytes + 0x24D8 + index * 0x3AC));
	std::memset(memory, 0, 0x37B0);
	*(Word*)memory |= 2u;
	DAT_004776f4 = (unsigned int)(unsigned long)memory;
	return memory;
}

void* PlayerManager_Create(void* (*allocate)(unsigned int size),
                           void* (*construct)(void* memory),
                           int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory)) {
	return CreateConstructedManager(0x37B0, allocate, construct, initialize,
	                                destroy, free_memory);
}

// 0x00414830 - Item manager factory: identical frame with a 0x9ED0-byte
// object and the item-side constructor/initializer pair.

// 0x00413810 - Construct the six retail entity banks, then apply the bulk
// clear/live-bit/publication tail. The intermediate flag and sentinel stores
// in retail are all overwritten by that same bulk clear.
void* ItemManager_Construct(void* memory) {
	static const unsigned int offsets[] = {
		0x10, 0x24C8, 0x4980, 0x6A8C, 0x793C, 0x8094
	};
	static const int counts[] = { 10, 10, 9, 4, 2, 7 };
	Byte* bytes = (Byte*)memory;
	for (unsigned int bank = 0; bank != 6; ++bank)
		for (int index = 0; index != counts[bank]; ++index)
			Entity_Constructor(
			    (Entity*)(bytes + offsets[bank] + index * 0x3AC));
	std::memset(memory, 0, 0x9ED0);
	*(Word*)memory |= 2u;
	DAT_0047770c = (unsigned int)(unsigned long)memory;
	return memory;
}

void* ItemManager_Create(void* (*allocate)(unsigned int size),
                         void* (*construct)(void* memory),
                         int (*initialize)(void),
                         void (*destroy)(void* manager),
                         void (*free_memory)(void* memory)) {
	return CreateConstructedManager(0x9ED0, allocate, construct, initialize,
	                                destroy, free_memory);
}

// 0x00429610 - Stage manager factory taking the stage script path: allocate
// the 0x2D4-byte object, vector-construct its eight 0x24-byte interpolator
// slots at +0xA0, zero the whole object, then run the script initializer;
// failure destroys and frees the half-built manager.
void* StageManager_CreateFromScript(
    const char* script_path, void* (*allocate)(unsigned int size),
    void (*construct_slots)(void* slots, int stride, int count),
    int (*initialize)(const char* script_path), void (*destroy)(void* manager),
    void (*free_memory)(void* memory)) {
	Word* manager = (Word*)allocate(0x2D4);
	if (manager != 0) {
		construct_slots(manager + 0x28, 0x24, 8);
		for (int index = 0; index < 0xB5; ++index) manager[index] = 0;
	}
	if (initialize(script_path) != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}

// 0x0041AED0 - Effect manager factory: allocate the 0x21CEC0-byte pool,
// vector-construct the 0x896 effect slots (0x3F0 bytes each) at +0x14, zero
// the object, set the alive bit (|= 2), publish the global pointer, then
// run the initializer; failure destroys and frees the pool.
void* EffectManager_Create(void* (*allocate)(unsigned int size),
                           void (*construct_slots)(void* slots, int stride,
                                                   int count),
                           void** global_slot, int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory)) {
	Word* manager = (Word*)allocate(0x21CEC0);
	if (manager != 0) {
		construct_slots(manager + 5, 0x3F0, 0x896);
		for (int index = 0; index < 0x873B0; ++index) manager[index] = 0;
		manager[0] |= 2u;
		*global_slot = manager;
	}
	if (initialize() != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}
