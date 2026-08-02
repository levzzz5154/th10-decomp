#include "th10/game/bullet_manager.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/runtime/missing_edge.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern void* g_pGameStateManager;
extern unsigned int DAT_00491be4;
extern int* ResourceManager_FindResource(int type, void* manager,
                                         const char* name);

namespace {
BulletPoolRuntimeBindings g_bullet_pool_bindings = {};

int __fastcall BulletPool_UpdateCallback(void* owner) {
    if (g_bullet_pool_bindings.update == 0)
        Runtime_MissingEdge(0x004065C0u, "bullet-pool update");
    return g_bullet_pool_bindings.update(owner);
}

int __fastcall BulletPool_DrawCallback(void* owner) {
    if (g_bullet_pool_bindings.draw == 0)
        Runtime_MissingEdge(0x004067A0u, "bullet-pool draw");
    return g_bullet_pool_bindings.draw(owner);
}
}  // namespace

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

void BulletPoolRuntime_SetBindings(
        const BulletPoolRuntimeBindings* bindings) {
    if (bindings != 0)
        g_bullet_pool_bindings = *bindings;
    else
        std::memset(&g_bullet_pool_bindings, 0,
                    sizeof(g_bullet_pool_bindings));
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
