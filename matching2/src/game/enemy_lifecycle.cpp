#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.

// Shared per-frame clock advance used by the update callbacks below. When
// the global frame-scale control sits inside the normal span the frame
// counter simply increments; otherwise the scaled control value is
// accumulated and the frame is re-derived by truncation.
static void AdvanceFrameClock(PlayerDeathClock* clock, float span_low,
                              float span_high, float frame_step,
                              long long (*float_to_long)(float value)) {
	float control = *clock->control;
	clock->previous = clock->frame;
	if (span_low < control && control < span_high) {
		clock->timer += frame_step;
		clock->frame += 1;
	} else {
		clock->timer += control;
		clock->frame = (int)float_to_long(clock->timer);
	}
}

#include <cmath>
#include <cstring>

namespace {



} // namespace

#include <cmath>
#include <cstring>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).




} // namespace

// 0x004066E0 - Walk one enemy list row and refresh every node's collision
// snapshot: the hitbox center takes the node position plus the playfield
// offset, and nodes with pending-rotation flag 0x8000000 recompute their
// sprite angle (facing normalized against a quarter turn) and arm dirty
// flag bit 2 before the shared state manager is marked dirty.
int EnemyList_SyncHitboxes(HitboxEnemy* head, float offset_x, float offset_y,
                           float (*normalize_angle)(float angle,
                                                    float quarter_turn),
                           void (*mark_dirty)(void* state), void* state) {
    for (HitboxEnemy* node = head; node != 0; node = node->next) {
        node->hitbox.x = node->position.x + offset_x;
        node->hitbox.y = node->position.y + offset_y;
        node->hitbox.z = node->position.z;
        if ((node->flags & 0x8000000u) != 0) {
            node->sprite_angle =
                normalize_angle(node->facing_angle, 1.5707964f);
            node->flags = node->flags | 4;
        }
        if (mark_dirty != 0) mark_dirty(state);
    }
    return 1;
}

// 0x0040E6A0 - Sweep the live enemy list when the player dies: any enemy
// that is not protected (no 0x50/0xC000 state bits) or that is explicitly
// marked (bit 7) hands its pending drop to the capture handler and is
// tagged 0x20000 (dead-for-capture). The owner's frame clock then advances.
void EnemyList_MarkDeadForCapture(CaptureNode* head,
                                  void* const* handler_table,
                                  void (*notify)(void* handler),
                                  PlayerDeathClock* clock, float span_low,
                                  float span_high, float frame_step,
                                  long long (*float_to_long)(float value)) {
	for (CaptureNode* node = head; node != 0; node = node->next) {
		CaptureEnemy* enemy = node->enemy;
		Word flags = enemy->flags;
		int unprotected = (flags & 0x50u) == 0 && (flags & 0xC000u) == 0;
		if (unprotected || (flags & 0x80u) != 0) {
			if (enemy->drop_slot >= 0) {
				notify(handler_table[enemy->drop_index]);
			}
			enemy->flags |= 0x20000u;
		}
	}
	AdvanceFrameClock(clock, span_low, span_high, frame_step, float_to_long);
}

// 0x0040D750 - Step every live enemy's position interpolator. An enemy
// whose interpolator completes (and that is not already dead-for-capture)
// loses its interpolating bit (0x400); otherwise it is retired through its
// virtual retire hook with mode 1. Advances the frame clock, returns 1.
int EnemyList_TickInterpolators(InterpNode* head,
                                int (*step_interpolator)(void* interpolator),
                                void (*retire)(InterpEnemy* enemy,
                                               int mode),
                                PlayerDeathClock* clock, float span_low,
                                float span_high, float frame_step,
                                long long (*float_to_long)(float value)) {
	InterpNode* node = head;
	while (node != 0) {
		InterpNode* next = node->next;
		InterpEnemy* enemy = node->enemy;
		if ((enemy->flags & 0x20000u) == 0 &&
		    step_interpolator(enemy->interpolator) == 0) {
			enemy->flags &= ~0x400u;
		} else if (enemy != 0) {
			retire(enemy, 1);
		}
		node = next;
	}
	AdvanceFrameClock(clock, span_low, span_high, frame_step, float_to_long);
	return 1;
}

// 0x0040B110 - table-driven enemy spawn helper: acquires an effect VM on
// layer 15 with the persistent flag, assigns the table sprite, refreshes
// the layout, resolves the enemy instance (zeroing the handle when the
// lookup fails), runs the optional spawn callback, and copies the table
// anchor into the enemy.
void EnemySpawner_CreateFromTable(const SpawnEntry* table, int index,
                                  int handle, int* result_slot,
                                  SpawnEnv* env) {
	const SpawnEntry* entry = &table[index];
	SpawnEffectVm* vm = env->acquire_effect();
	vm->layer = 0xF;
	vm->flags |= 0x40000000u;
	env->assign_sprite(vm, entry->sprite_id);
	env->refresh_layout(env->state_manager);
	SpawnedEnemy* enemy = env->resolve_enemy(env->state_manager, handle);
	if (enemy == 0) handle = 0;
	if (entry->on_spawn != 0) entry->on_spawn();
	if (enemy != 0) {
		enemy->anchor_x = entry->anchor_x;
		enemy->anchor_y = entry->anchor_y;
	}
	*result_slot = handle;
}

// 0x00408100 - blast-radius enemy kill sweep: every live, non-dying enemy
// (optionally excluding bosses) whose expanded radius touches the blast
// circle is killed; enemies that do not convert into items spawn the
// downward burst effect when requested.
int EnemyPool_BlastRadius(BlastEnemy* enemies, int count,
                          const float* center, float radius,
                          int spawn_effects, int skip_bosses,
                          BlastEnv* env) {
	for (int i = 0; i < count; ++i) {
		BlastEnemy* enemy = &enemies[i];
		if (enemy->state == 0 || enemy->state == 3) continue;
		if (skip_bosses != 0 && enemy->boss_flag != 0) continue;
		float dx = enemy->position[0] - center[0];
		float dy = enemy->position[1] - center[1];
		float reach = enemy->size * env->half_scale + radius;
		if (dx * dx + dy * dy <= reach * reach) {
			env->kill_enemy(enemy);
			if (env->convert_to_item(enemy->position, 2.0f, 2.0f) == 0 &&
			    spawn_effects != 0) {
				env->spawn_effect(env->effect_pool, 8, 0xFFFFFFFFu, -1.5707964f,
				                  0.6f);
			}
		}
	}
	return 0;
}

// 0x0040DAE0 - enemy destructor: unlink from the manager ring, release the
// boss slot, flag attached bullet groups for cancellation, clear effect
// registry references, and free the allocation chain.
void Enemy_Destroy(DtorEnemy* enemy, DtorEnv* env) {
	DtorManager* manager = env->manager;
	enemy->vtable = env->live_vtable;

	if (manager->head == &enemy->node) {
		manager->head = enemy->node.next;
	}
	if (manager->tail == &enemy->node) {
		manager->tail = enemy->node.prev;
	}
	if (enemy->node.next != 0) {
		enemy->node.next->prev = enemy->node.prev;
	}
	if (enemy->node.prev != 0) {
		enemy->node.prev->next = enemy->node.next;
	}
	enemy->node.next = 0;
	enemy->node.prev = 0;
	manager->count -= 1;

	if ((enemy->slot_flags & 0x8000u) != 0) {
		manager->slots[enemy->slot_index] = 0;
	}

	for (int i = 0; i < 10; ++i) {
		int handle = enemy->handles[i];
		if (handle != 0) {
			RefNode* found = 0;
			for (RefNode* node = env->search_list_a; node != 0;
			     node = node->next) {
				if (node->value->id == handle) {
					found = node;
					break;
				}
			}
			if (found == 0) {
				for (RefNode* node = env->search_list_b; node != 0;
				     node = node->next) {
					if (node->value->id == handle) {
						found = node;
						break;
					}
				}
			}
			if (found != 0 && found->value != 0) {
				EnemyRef* ref = found->value;
				ref->flags |= 0x4000000u;
				if (ref->parent == 0) {
					for (RefNode* child = ref->children; child != 0;
					     child = child->next) {
						child->value->flags |= 0x4000000u;
					}
				}
			}
		}
		enemy->handles[i] = 0;
	}

	EffectRegistry* effects = env->effects;
	if (effects != 0) {
		if (*effects->focus_slot == enemy) {
			*effects->focus_slot = 0;
			*effects->focus_flag = 0;
		}
		for (int i = 0; i < effects->slot_count; ++i) {
			if (effects->slots[i].owner == enemy) {
				effects->slots[i].owner = 0;
			}
		}
	}

	enemy->vtable = env->dead_vtable;
	ChainAlloc* block = enemy->chain;
	while (block != 0) {
		ChainAlloc* next = block->next;
		env->free_block(block->data);
		env->free_block(block);
		block = next;
	}
}
