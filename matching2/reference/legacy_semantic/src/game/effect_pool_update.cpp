#include "th10/game/effect_pool_update.hpp"

// 0x00428280 - effect-pool per-frame update. Walks all 128 effect slots:
// releases sound-driven kinds when the channel budget, pause menu, or a
// missing game owner demands it, honors deferred stop requests, runs the
// per-type callback, advances polar/linear motion, retires slots whose main
// animation object is gone (requesting deletion of the companion tree),
// culls established non-sound effects once off-screen, publishes screen-
// space positions to both animation objects, and advances the slot frame
// timer. Always returns 0.
int EffectPool_Update(EffectPoolSlot* slots, EffectPoolEnv* env) {
	for (int i = 0; i < 128; ++i) {
		EffectPoolSlot* slot = &slots[i];
		if (slot->state == 0)
			continue;
		const EffectPoolRecord* record = slot->record;

		// Sound-driven kinds release their scripts when the channel budget
		// is exhausted or the record's channel index falls outside it...
		if (record->kind == 3 && slot->state == 1 &&
		    (env->sound_budget < 0 ||
		     record->index - 1 >= env->sound_channel_limit)) {
			env->release_handle(&slot->handle1);
			env->release_handle(&slot->handle2);
			slot->state = 2;
			env->sound_slots[(int)record->index] = 0;
		}
		// ...and when the pause menu opens or the game owner is gone.
		if (record->kind == 3 && slot->state == 1 &&
		    (env->pause_menu_open != 0 || env->game_inactive != 0)) {
			slot->state = 2;
			env->release_handle(&slot->handle1);
			env->release_handle(&slot->handle2);
			env->sound_slots[(int)record->index] = 0;
		}
		// Deferred stop request for still-active sound kinds.
		if (record->kind == 3 && slot->suppress == 0 && slot->state == 1 &&
		    slot->stop_request == 1) {
			env->stop_at_frame3(&slot->handle1);
			slot->stop_request = 0;
		}
		slot->suppress = 0;
		if (record->tick != 0)
			record->tick(env->manager, slot);

		// Motion: polar accumulation or a linear polar velocity rebuild.
		if ((slot->motion_flags & 1u) != 0) {
			slot->radius += slot->radius_step;
			slot->angle = env->wrap_angle(slot->rate + slot->angle);
		} else {
			env->set_polar(slot->velocity, slot->angle, slot->rate);
			slot->velocity[2] = 0.0f;
		}
		env->advance_motion(slot->position);

		// Resolve the main animation object.
		EffectPoolVm* vm =
		    slot->handle1 != 0 ? env->find_vm(slot->handle1) : 0;
		if (vm == 0) {
			// The main script ended: free the slot and request deletion of
			// the companion tree.
			slot->state = 0;
			if (slot->handle2 != 0) {
				EffectPoolVm* companion = env->find_vm(slot->handle2);
				if (companion != 0) {
					companion->flags |= 0x4000000u;
					if (companion->child_membership == 0) {
						for (EffectPoolVmNode* node = companion->children;
						     node != 0; node = node->next)
							node->vm->flags |= 0x4000000u;
					}
				}
			}
			slot->handle2 = 0;
			slot->handle1 = 0;
			continue;
		}

		// Established non-sound effects are culled once off-screen; the
		// extents come from the sprite dimensions scaled by the object's
		// growth factors.
		if (record->kind != 3 && slot->frame >= 10 &&
		    env->outside_viewport(slot->position,
		                          vm->sprite->height * vm->growth_x,
		                          vm->sprite->width * vm->growth_y) != 0) {
			env->release_root(slot->handle1);
			slot->handle1 = 0;
			slot->state = 0;
			continue;
		}

		// Keep: publish the screen-space position to both objects.
		vm->position[0] = slot->position[0] + 224.0f;
		vm->position[1] = slot->position[1] + 16.0f;
		vm->position[2] = slot->position[2];
		if (slot->handle2 != 0) {
			EffectPoolVm* companion = env->find_vm(slot->handle2);
			if (companion != 0) {
				companion->position[0] = slot->position[0] + 224.0f;
				companion->position[1] = slot->position[1] + 16.0f;
				companion->position[2] = slot->position[2];
			} else {
				slot->handle2 = 0;
			}
		}
		if ((vm->flags & 0x8000000u) != 0) {
			vm->angle = slot->angle;
			vm->flags |= 4u;
		}
		// Inlined frame-timer advance by one frame.
		slot->previous_frame = slot->frame;
		const float speed = *slot->game_speed;
		if (speed <= 0.99000001f || speed >= 1.01f) {
			slot->frame_elapsed += speed;
			slot->frame = (int)(unsigned long long)slot->frame_elapsed;
		} else {
			slot->frame = slot->frame + 1;
			slot->frame_elapsed += 1.0f;
		}
	}
	return 0;
}
