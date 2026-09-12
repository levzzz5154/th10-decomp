#include "th10/game/trigger_activation.hpp"

namespace {
void ResetClock(TriggerClock* clock, float* frame_scale) {
	if ((clock->flags & 1u) == 0) {
		clock->frame = 0;
		clock->previous = (int)0xFFF0BDC1u;
		clock->timer = 0.0f;
		clock->control = frame_scale;
		clock->flags |= 1u;
	}
	clock->frame = 0;
	clock->timer = 0.0f;
	clock->previous = -1;
}
} // namespace

// 0x00426CF0 - enters the trigger's active state, creates the lead effect and
// its 32 companions, resets both retail clocks, optionally plays the cue,
// selects the trigger animation, and clears the late-stage visibility bits.
void TriggerRegion_Activate(TriggerActivation* trigger,
                            TriggerActivationEnv* env) {
	trigger->mode = 4;
	env->spawn_effect(0x162, trigger);
	for (int index = 0; index < 32; ++index) {
		env->spawn_effect(0x163, trigger);
	}

	ResetClock(&trigger->activation_clock, env->frame_scale);
	if (!env->sound_suppressed) {
		env->play_sound(0);
	}

	if ((trigger->cooldown_clock.flags & 1u) == 0) {
		trigger->cooldown_clock.frame = 0;
		trigger->cooldown_clock.previous = (int)0xFFF0BDC1u;
		trigger->cooldown_clock.timer = 0.0f;
		trigger->cooldown_clock.control = env->frame_scale;
		trigger->cooldown_clock.flags |= 1u;
	}
	trigger->cooldown_clock.frame = 6;
	trigger->cooldown_clock.timer = 6.0f;
	trigger->cooldown_clock.previous = 5;
	env->set_animation(trigger->animation_handle);

	if (env->stage_counter > 59) {
		if (env->stage_latch != 0) {
			*env->stage_latch = 0;
		}
		for (int index = 0; index < 8; ++index) {
			if (env->stage_flags[index] != 0) {
				*env->stage_flags[index] &= ~2u;
			}
		}
	}
}
