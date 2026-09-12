#include "th10/game/bullet_manager.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/math/angle.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern void* g_pGameStateManager;
extern "C" unsigned long dword_477810;
extern "C" uint32_t DAT_00476f78;   // shared frame-scale, by address
extern unsigned int DAT_00491be4;
extern int* ResourceManager_FindResource(int type, void* manager,
                                         const char* name);

namespace {
// The retail update edge (0x004065C0) is reconstructed as the named
// BulletPool_UpdateSweep below; the per-bullet check twin (retail
// sub_406240) is injected through BulletPoolRuntime_SetUpdateEnv and is
// elided (null) until then.
BulletPoolUpdateEnv g_bullet_pool_update_env = {};

int __fastcall BulletPool_UpdateCallback(void* owner) {
    return BulletPool_UpdateSweep(owner, &g_bullet_pool_update_env);
}

int __fastcall BulletPool_DrawCallback(void* owner) {
    // Retail 0x004067A0: the bullet-pool draw edge.  When the published
    // game-UI manager (0x00477810) is absent or its +88 flag bit 2 is clear,
    // walk the six enemy rows (heads at +20 + 4*row) and refresh every node's
    // hitbox snapshot through the recovered 0x004066E0 loop, with the
    // retail's fixed playfield offsets (224.0, 16.0).  The retail loop also
    // runs the 0x004451C0 per-node dispatch, which this tree models only as
    // the draw-mode claim; the dirty-flag callback is left null accordingly.
    if (dword_477810 == 0 ||
        (*(unsigned char*)((char*)dword_477810 + 88) & 4) == 0) {
        for (int row = 0; row < 6; ++row) {
            EnemyList_SyncHitboxes(
                (HitboxEnemy*)((char*)owner + 20 + 4 * row),
                224.0f, 16.0f, Angle_NormalizeSum, 0, owner);
        }
    }
    return 1;
}
}  // namespace

// 0x004065C0 - bullet-pool update sweep.  Clears the active count (+0x5C)
// and the six head/tail dword lists (heads at +20+4*row, tails at
// +44+4*row), then walks the 2000 payload records at +0x60 (stride 0x7F0).
// A record whose active WORD (payload +0x446) is nonzero is admitted when
// the UI-manager capture state is up (dword_477810 +88 flags bits 2 and
// 0x400, read once like the retail body) or the injected per-bullet check
// (retail sub_406240, via env->update_bullet) reports the bullet alive; a
// null hook elides the check, so the capture path is then the only
// admission.  Survivors relink at the row named by the row dword (payload
// +0x460): tail->+0x44C = new node, the slot's own link (payload +0x44C) is
// cleared, and the count increments.  The interpolator clock then advances:
// the counter copy (payload +0x3F8) takes the old counter (payload +0x3FC),
// then either the damp path (drive <= 0.99 or >= 1.01: value payload +0x400
// += drive, counter = (int)value) or the ramp path (value += 1.0, counter +
// 1) - the same 0.99/1.01/1.0 constants as the 0x0042B9A0 effect sweep, but
// the >= 1.01 arm is a real gate here (the asm has no parity-flag NaN
// filter).  The head/tail lists and the node links stay retail-width dwords
// holding 32-bit record pointers; on a 64-bit host the pool record must sit
// below 4 GiB for the values to round-trip (the suite's 32-bit-retail
// fixture convention).  Returns 1.
int BulletPool_UpdateSweep(void* owner, const BulletPoolUpdateEnv* env) {
    unsigned char* bytes = (unsigned char*)owner;
    int* active_count = (int*)(bytes + 0x5C);
    *active_count = 0;
    uint32_t* head_slots = (uint32_t*)(bytes + 0x14);  // a1[5+row]
    uint32_t* tail_slots = (uint32_t*)(bytes + 0x2C);  // a1[11+row]
    for (int row = 0; row < 6; ++row) {
        head_slots[row] = 0;
        tail_slots[row] = 0;
    }
    unsigned char* payload = bytes + 0x60;
    for (int index = 0; index < 2000; ++index, payload += 0x7F0) {
        if (*(unsigned short*)(payload + 0x446) == 0) continue;  // active
        unsigned long manager = dword_477810;
        unsigned int flags = manager != 0
            ? *(unsigned int*)((unsigned char*)manager + 88) : 0;
        if ((flags & 2) == 0 || (flags & 0x400) == 0) {
            if (env->update_bullet == 0) continue;  // check elided
            if (env->update_bullet(payload) != 0) continue;  // destroyed
        }
        const uint32_t handle = (uint32_t)(uintptr_t)payload;
        int row_index = *(int*)(payload + 0x460);
        if (head_slots[row_index] != 0) {
            *(uint32_t*)((unsigned char*)(uintptr_t)tail_slots[row_index]
                         + 0x44C) = handle;
        } else {
            head_slots[row_index] = handle;
        }
        tail_slots[row_index] = handle;
        *(uint32_t*)(payload + 0x44C) = 0;
        *active_count += 1;
        int counter = *(int*)(payload + 0x3FC);
        *(int*)(payload + 0x3F8) = counter;
        float drive = *(float*)(*(void**)(payload + 0x404));
        if (drive <= 0.99f || drive >= 1.01f) {
            float value = *(float*)(payload + 0x400) + drive;
            *(float*)(payload + 0x400) = value;
            *(int*)(payload + 0x3FC) = (int)value;
        } else {
            *(float*)(payload + 0x400) += 1.0f;
            *(int*)(payload + 0x3FC) = counter + 1;
        }
    }
    return 1;
}

void BulletPoolRuntime_SetUpdateEnv(const BulletPoolUpdateEnv* env) {
    if (env != 0)
        g_bullet_pool_update_env = *env;
    else
        std::memset(&g_bullet_pool_update_env, 0,
                    sizeof(g_bullet_pool_update_env));
}

// Retail sub_405BE0: the pool slot destroy leaf.  Clears the active word at
// +0x446 and rewinds both interpolator pairs (the +0x3F8..0x408 and
// +0x40C..0x41C blocks) to their free defaults.  The per-bullet hook calls
// this when the slot's ANM script has run to its end or the slot self-
// destructs; the sweep then drops the payload from the relink lists.
void BulletPool_RetireSlot(void* payload) {
    if (payload == 0)
        return;
    unsigned char* bytes = static_cast<unsigned char*>(payload);
    *reinterpret_cast<unsigned short*>(bytes + 0x446) = 0;
    uint32_t* words = reinterpret_cast<uint32_t*>(bytes);
    words[0x3F8 / 4] = 0xFFF0BDC1;
    words[0x3FC / 4] = 0;
    words[0x400 / 4] = 0;
    words[0x404 / 4] = static_cast<uint32_t>(
        reinterpret_cast<uintptr_t>(&DAT_00476f78));
    words[0x408 / 4] |= 1u;     // clock 1 armed bit
    words[0x40C / 4] = 0xFFFFFFFF;
    words[0x410 / 4] = 0;
    words[0x414 / 4] = 0;
    words[0x418 / 4] = static_cast<uint32_t>(
        reinterpret_cast<uintptr_t>(&DAT_00476f78));
    words[0x41C / 4] |= 1u;    // clock 2 armed bit
}

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


#include <cmath>
#include <cstring>

namespace {

// Shared retail interpolator clock advance: while the frame-scale control
// stays inside the fixed-step span the clock ticks one frame per call,
// otherwise it accumulates the control value and rederives the frame index.
void AdvanceClock(FrameClock* clock, const ClockEnv* env) {
	clock->previous = clock->frame;
	float control = *clock->control;
	if (env->span_low < control && control < env->span_high) {
		clock->timer += env->frame_step;
		clock->frame += 1;
	} else {
		clock->timer += control;
		clock->frame = (int)env->float_to_long(clock->timer);
	}
}


} // namespace

#include <cmath>
#include <cstring>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).




} // namespace

// 0x00405E20 - Bullet manager registration hook. Retail mounts "bullet.anm"
// through the shared state manager (bank 7); a failed mount logs the packed
// error string and aborts with -1. On success the free-slot cursor is armed
// at the pool base (+0x60), the state word (+0x3E07A6) is set to 5, and the
// update and draw callbacks are registered with the auto-release bit
// cleared, exactly like the effect manager hook.
int BulletManager_OnRegister(ManagerRegistration* manager,
                             void** animation_slot,
                             void* (*mount_animation)(int bank, void* state,
                                                      const char* name),
                             void* state_manager,
                             void (*report_error)(const char* message,
                                                  const char* argument),
                             const char* error_message,
                             const char* error_argument, void** cursor_out,
                             void* pool_base, unsigned short* state_word,
                             void* update_callback, void* draw_callback,
                             SchedulerCallbackNode* (*create)(void* callback),
                             void (*enqueue_update)(void* queue),
                             void (*enqueue_draw)(void* queue), void* queue) {
    void* animation = mount_animation(7, state_manager, "bullet.anm");
    *animation_slot = animation;
    if (animation == 0) {
        if (report_error != 0) report_error(error_message, error_argument);
        return -1;
    }
    *cursor_out = pool_base;
    *state_word = 5;
    manager->update = Scheduler_RegisterOwnedCallback(
        manager, update_callback, create, enqueue_update, queue);
    manager->draw = Scheduler_RegisterOwnedCallback(
        manager, draw_callback, create, enqueue_draw, queue);
    return 0;
}

// 0x00405E20 - Resolve bullet.anm, initialize the free cursor/state word, and
// install the retail update/draw callback pair.
int BulletPoolRuntime_Initialize(void* manager) {
    if (manager == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)manager;
    int* animation =
        ResourceManager_FindResource(7, g_pGameStateManager, "bullet.anm");
    *(int**)(bytes + 0x3E0B50) = animation;
    if (animation == 0)
        return -1;
    *(void**)(bytes + 0x10) = bytes + 0x60;
    *(unsigned short*)(bytes + 0x3E07A6) = 5;

    SchedulerCallback* update =
        SchedulerCallback_Create(BulletPool_UpdateCallback);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = manager;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* draw =
        SchedulerCallback_Create(BulletPool_DrawCallback);
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

// 0x00405ED0 - Reset the bullet pool. Retail rebinds the pool's animation
// handle (retail 0x004493E0), zeroes the entire 0xF82BC-dword pool that
// starts at +0x60, points the free-slot cursor (+0x10) back at the pool
// base, and re-arms the state word (+0x3E07A6) with 5.
void BulletManager_ResetPool(void (*rebind_animation)(void* handle,
                                                      void* animation),
                             void* handle, void* animation,
                             Word* pool_words,
                             unsigned int pool_word_count, void** cursor_out,
                             void* pool_base, unsigned short* state_word) {
    if (rebind_animation != 0) rebind_animation(handle, animation);
    for (unsigned int index = 0; index < pool_word_count; ++index) {
        pool_words[index] = 0;
    }
    *cursor_out = pool_base;
    *state_word = 5;
}

// --- Enemy, boss, and UI leaves ---------------------------------------------------

// 0x00404450 - Re-activate the bullet manager's scheduler nodes after a
// reload and re-register every sprite in every script bank, assigning each
// record a fresh sequential sprite index. Finally the pool cursor rewinds
// to the pool base.
void BulletManager_ActivateSprites(BulletHost* host,
                                   void (*register_sprite)(void* pool)) {
	host->update->flags |= 2u;
	host->draw->flags |= 2u;
	host->overlay->flags |= 2u;
	int next_index = 0;
	for (int bank = 0; bank < *host->bank_count; ++bank) {
		BulletSpriteBank* bank_data = host->banks[bank];
		bank_data->active = 1;
		BulletSpriteRecord* record = bank_data->records;
		while (record->id >= 0) {
			register_sprite(host->sprite_pool);
			record->assigned = (short)next_index;
			++next_index;
			record = (BulletSpriteRecord*)((char*)record + record->stride);
		}
	}
	host->cursor = host->pool_base;
}

// 0x00406060 - Bullet manager factory: allocate the 0x3E0B54-byte pool,
// vector-construct the 0x7D1 bullet slots (0x7F0 bytes each) at +0x60, zero
// the whole object, publish it in the global slot, then run the resource
// initializer; failure destroys and frees the pool.
void* BulletManager_Create(void* (*allocate)(unsigned int size),
                           void (*construct_slots)(void* slots, int stride,
                                                   int count),
                           void** global_slot, int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory)) {
	Word* manager = (Word*)allocate(0x3E0B54);
	if (manager != 0) {
		construct_slots(manager + 0x18, 0x7F0, 0x7D1);
		for (int index = 0; index < 0xF82D5; ++index) manager[index] = 0;
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

// 0x00404F30 - Construct one bullet slot: run the shared base initializer,
// clear the nine motion accumulators, reset both scale bytes to 0x10,
// stamp the slot id, and initialize the slot's timer block.
void BulletSlot_Construct(BulletSlot* slot, short id, void* base,
                          void (*base_init)(void* base, void* slot),
                          void* timer, void (*init_timer)(void* timer)) {
	base_init(base, slot);
	for (int index = 0; index < 9; ++index) slot->motion[index] = 0;
	slot->scale_a = 0x10;
	slot->scale_b = 0x10;
	slot->id = id;
	init_timer(timer);
}

// 0x00405300 - Select the active shot type: point the active-shot pointer
// at the indexed 0x118-byte table entry, refresh the shot state, upload the
// entry's palette block (at +0xCC) through the device, and remember the
// selected index.
void BulletManager_SelectShotType(void** active_slot, char* shot_table,
                                  int stride, int index,
                                  void (*refresh)(void), void* device,
                                  void (*upload_palette)(void* device,
                                                         void* palette),
                                  int palette_offset, int* current_index) {
	char* entry = shot_table + index * stride;
	*active_slot = entry;
	refresh();
	upload_palette(device, entry + palette_offset);
	*current_index = index;
}

// 0x004065C0 - bullet manager relink pass: clears the six per-layer draw
// lists, updates each live bullet (unless the player capture state freezes
// them), re-links survivors into their layer list, and advances each
// bullet's interpolator clock.
int BulletManager_RelinkActive(BulletLinkManager* manager,
                               LinkBullet* bullets, int count,
                               BulletLinkEnv* env) {
	manager->active_count = 0;
	for (int layer = 0; layer < 6; ++layer) {
		manager->heads[layer] = 0;
		manager->tails[layer] = 0;
	}
	for (int i = 0; i < count; ++i) {
		LinkBullet* bullet = &bullets[i];
		if (bullet->state == 0) continue;
		if (env->player_flags == 0 || (*env->player_flags & 2) == 0 ||
		    (*env->player_flags & 0x400) == 0) {
			if (env->update_bullet(bullet) != 0) continue;
		}
		int layer = (int)bullet->layer;
		if (manager->heads[layer] == 0) {
			manager->heads[layer] = bullet;
		} else {
			manager->tails[layer]->next = bullet;
		}
		manager->tails[layer] = bullet;
		bullet->age = 0.0f;
		manager->active_count += 1;
		AdvanceClock(&bullet->clock, &env->clock_env);
	}
	return 1;
}

// 0x00402720 - bullet manager draw callback: skipped while hidden or during
// a long freeze; otherwise clears the recoil accumulators, normalizes the
// aim vector, draws the eight layer batches (plus three overlay batches at
// unit scale when pending), and publishes the camera block snapshot.
int BulletManager_OnDraw(BulletDrawHost* host, BulletDrawEnv* env) {
	if ((host->flags & 8) == 0 &&
	    ((host->flags & 4) == 0 || host->freeze_timer < 0x3C)) {
		for (int i = 0; i < 5; ++i) host->recoil[i] = 0.0f;
		env->normalize(host->aim_normalized, host->aim_source);
		host->ambient_color = 0x808080;
		env->prepare_common_state();
		env->refresh_layout(host);
		for (int i = 0; i < 8; ++i) env->draw_batch(host->layer_batches[i]);
		float saved_scale = *env->global_scale;
		if (host->overlay_pending != 0) {
			*env->global_scale = 1.0f;
			for (int i = 0; i < 3; ++i) env->draw_batch(host->overlay_batches[i]);
		}
		*env->global_scale = saved_scale;
		host->overlay_pending = 0;
		for (int i = 0; i < 0x46; ++i) {
			env->camera_snapshot[i] = host->camera_block[i];
		}
		host->draw_counter += 1;
	}
	return 1;
}

// 0x0040C730 - resets a bullet ring container to its empty state.
void BulletRing_Reset(BulletRing* ring) {
	ring->flags &= ~1u;
	ring->node.next = 0;
	ring->node.prev = 0;
	ring->self = ring;
	ring->sentinel = -1;
	ring->control_flags = 0;
	ring->head = &ring->node;
	ring->cursor = &ring->node;
	ring->count_a = 0;
	ring->count_b = 0;
}
