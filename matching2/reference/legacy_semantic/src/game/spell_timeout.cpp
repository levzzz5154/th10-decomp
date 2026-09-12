#include "th10/game/spell_timeout.hpp"

#include <cmath>

// 0x004269D0 - Enter the spell/attack timeout transition.
void SpellTimeout_EnterTransition(SpellTimeoutHost* host,
                                  SpellTimeoutEnv* env) {
	const int excess = *env->bonus_pool - 5000;
	*env->bonus_pool -= excess / 3;
	if (*env->bonus_pool < 5000) *env->bonus_pool = 5000;

	*env->countdown -= 1;
	if (*env->countdown >= 0 && env->publish_countdown != 0) {
		env->publish_countdown(*env->countdown);
	}

	host->phase = 2;
	SpellTimeoutTimer* short_timer = &host->short_timer;
	if ((short_timer->flags & 1u) == 0) {
		short_timer->current = 0;
		short_timer->target = -999999;
		short_timer->previous_bits = 0;
		short_timer->speed = env->frame_speed;
		short_timer->flags |= 1u;
	}
	short_timer->current = 0;
	short_timer->previous_bits = 0;
	short_timer->target = -1;

	SpellTimeoutTimer* grace = &host->grace_timer;
	if ((grace->flags & 1u) == 0) {
		grace->current = 0;
		grace->target = -999999;
		grace->previous_bits = 0;
		grace->speed = env->frame_speed;
		grace->flags |= 1u;
	}
	grace->current = 180;
	grace->previous_bits = 0x43340000; // float image of 180.0f
	grace->target = 179;

	if (env->stop_sound != 0) env->stop_sound(host->sound_owner);
	for (int index = 0; index < 4; ++index) {
		SpellTimeoutAnimationPair* pair = &host->animation_pairs[index];
		pair->marker = 0;
		if (pair->primary_handle != 0 && env->retire_animation != 0) {
			env->retire_animation(pair->primary_handle);
		}
		if (pair->secondary_handle != 0 && env->retire_animation != 0) {
			env->retire_animation(pair->secondary_handle);
		}
	}

	host->caution_active = 0;
	if (env->warning_mode != 1 && env->show_caution != 0) {
		env->show_caution("Caution!");
	}

	if (env->player->stage_frames >= 60) {
		env->player->charge = 0;
		env->player->main_flags &= ~2u;
		for (int index = 0; index < 8; ++index) {
			env->player->option_flags[index] &= ~2u;
		}
	}

	int gauge = *env->transition_gauge - 1024;
	if (gauge > 1024) gauge = 1024;
	if (gauge < -1024) gauge = -1024;
	*env->transition_gauge = gauge;
}
