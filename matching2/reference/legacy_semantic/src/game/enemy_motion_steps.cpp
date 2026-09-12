#include "th10/game/enemy_motion_steps.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

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

// Lazy interpolator registration: bind the control pointer to the global
// frame-scale slot the first time the block is used.
void RegisterClock(RegisteredClock* registered, float* frame_scale) {
	if ((registered->flags & 1) == 0) {
		registered->clock.frame = 0;
		registered->clock.previous = (int)0xFFF0BDC1u;
		registered->clock.timer = 0.0f;
		registered->clock.control = frame_scale;
		registered->flags |= 1;
	}
}

} // namespace

#include <cmath>
#include <cstring>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).




} // namespace

#include <cmath>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).

} // namespace

// 0x00407560 - enemy acceleration step: while running, integrates the speed
// and velocity accelerations and re-derives the facing angle from the
// velocity; afterwards clears status bit 0x10. Always advances the clock.
void Enemy_AccelStep(AccelEnemy* enemy, float frame_scale,
                     float min_component, const ClockEnv* clock_env) {
	if (enemy->clock.frame < enemy->duration) {
		enemy->speed += frame_scale * enemy->speed_accel;
		enemy->velocity[0] += frame_scale * enemy->accel[0];
		enemy->velocity[1] += frame_scale * enemy->accel[1];
		enemy->velocity[2] += frame_scale * enemy->accel[2];
		if (min_component < fabsf(enemy->velocity[0]) ||
		    min_component < fabsf(enemy->velocity[1])) {
			enemy->angle = atan2f(enemy->velocity[1], enemy->velocity[0]);
		}
	} else {
		*enemy->status_flags &= ~0x10u;
	}
	AdvanceClock(&enemy->clock, clock_env);
}

// 0x00407EF0 - enemy homing turn step: while running, aims at the target
// (straight up when overlapping), turns toward it by the wrapped, limited
// turn amount scaled by the turn rate, and rebuilds the velocity from the
// new angle; afterwards clears status bit 0x04000000.
void Enemy_HomingStep(HomingEnemy* enemy, HomingEnv* env) {
	if (enemy->clock.frame < enemy->duration) {
		float dx = env->target_position[0] - enemy->position[0];
		float dy = env->target_position[1] - enemy->position[1];
		float aim;
		if (dx == 0.0f && dy == 0.0f) {
			aim = 1.5707964f;
		} else {
			aim = atan2f(dy, dx);
		}
		float wrapped = env->wrap_turn(enemy->turn_limit, aim);
		float limited = env->limit_turn(wrapped, enemy->angle);
		enemy->angle = env->wrap_turn(
		    enemy->angle, limited * enemy->turn_rate * env->frame_scale);
		env->set_velocity(enemy->velocity, enemy->angle, enemy->speed);
	} else {
		*enemy->status_flags &= ~0x04000000u;
	}
	AdvanceClock(&enemy->clock, &env->clock_env);
}

namespace {

// Shared body for the two ease steps (0x004078E0 / 0x00407780): while the
// ease is running the speed decays linearly toward zero; on completion the
// ambient loop stops, the repeat counter advances (clearing the caller's
// status bit at the limit), the final speed/angle are applied, and the
// clock is re-registered for the next segment.
void EaseStepCommon(EaseEnemy* enemy, EaseEnv* env,
                    Word clear_mask, int add_angle) {
	float eased;
	if (enemy->clock.clock.frame < enemy->duration) {
		eased = enemy->speed -
		        (enemy->speed * enemy->clock.clock.timer) / (float)enemy->duration;
	} else {
		if (0 <= enemy->ambient_sound) {
			env->stop_ambient_sound(env->ambient_channel, 0);
		}
		enemy->repeat_count += 1;
		if (enemy->repeat_limit <= enemy->repeat_count) {
			*enemy->status_flags &= ~clear_mask;
		}
		if (add_angle != 0) {
			enemy->angle += enemy->final_angle;
		} else {
			enemy->angle = enemy->final_angle;
		}
		eased = enemy->final_speed;
		enemy->speed = eased;
		RegisterClock(&enemy->clock, env->frame_scale);
		enemy->clock.clock.frame = 0;
		enemy->clock.clock.timer = 0.0f;
		enemy->clock.clock.previous = -1;
	}
	env->set_velocity(enemy->velocity, enemy->angle, eased);
	AdvanceClock(&enemy->clock.clock, &env->clock_env);
}

} // namespace

// 0x004078E0 - enemy ease-to-stop step (status bit 0x100, angle assigned).
void Enemy_EaseStopStep(EaseEnemy* enemy, EaseEnv* env) {
	EaseStepCommon(enemy, env, 0x100u, 0);
}

// 0x00407780 - enemy ease-with-turn step (status bit 0x40, angle added).
void Enemy_EaseTurnStep(EaseEnemy* enemy, EaseEnv* env) {
	EaseStepCommon(enemy, env, 0x40u, 1);
}

// 0x00407BE0 - bounces an enemy off the playfield walls: reflects the
// position and angle, floors the speed, and clears the bounce bits once the
// bounce budget is exhausted.
void Enemy_BounceStep(BounceEnemy* enemy, BounceEnv* env) {
	bool outside_x = enemy->x < env->min_x || enemy->x >= env->max_x;
	bool outside_y = enemy->y < env->min_y || enemy->y >= env->max_y;
	if (!outside_x && !outside_y) {
		return;
	}

	bool bounced = false;
	if (enemy->sound_id >= 0) {
		env->play_sound(env->sound_manager, 0);
	}

	if (outside_x) {
		enemy->angle = env->normalize_angle(-enemy->angle - env->pi, 0.0f);
		bounced = true;
		float reflect = (enemy->x < env->min_x) ? env->reflect_low
		                                        : env->reflect_high;
		enemy->x = reflect - enemy->x;
	}

	if ((enemy->flags & 0x8000000u) == 0 &&
	    (enemy->y < env->min_y ||
	     (enemy->y >= env->max_y && (enemy->flags & 0x400u) != 0))) {
		bounced = true;
		enemy->angle = -enemy->angle;
		if (enemy->y >= env->min_y) {
			enemy->y = (env->max_y - enemy->y) + env->max_y;
		} else {
			enemy->y = -enemy->y;
		}
	}

	if (env->speed_floor < enemy->floor_speed) {
		enemy->speed = enemy->floor_speed;
	}
	env->set_velocity(enemy->velocity, enemy->angle, enemy->speed);

	if (bounced) {
		enemy->bounce_count += 1;
	}
	if (enemy->bounce_limit <= enemy->bounce_count) {
		enemy->flags &= 0xF7FFF3FFu; // clears 0x8000000 and 0xC00
	}
}

// 0x00407A30 - homing step with deceleration and relaunch. While the embedded
// clock has not reached the configured duration, the enemy keeps its heading
// and its speed decays linearly toward zero. When the duration elapses, the
// relaunch fires: the sound plays (when the gate allows it), the relaunch
// counter advances (clearing mode bit 0x80 at the limit), the enemy re-aims
// at the player plus the configured angle offset, the speed is restored, and
// the clock restarts. Both paths publish the velocity and advance the clock.
void Enemy_HomingRelaunchStep(RelaunchEnemy* enemy, RelaunchEnv* env) {
	float speed;
	if (enemy->clock.clock.frame < enemy->duration) {
		speed = enemy->speed -
		        (enemy->speed * enemy->clock.clock.timer) / (float)enemy->duration;
	} else {
		if (enemy->sound_gate >= 0) {
			env->play_sound(env->sound_state, 0);
		}
		enemy->relaunch_count += 1;
		if (enemy->relaunch_limit <= enemy->relaunch_count) {
			enemy->mode_flags &= ~kEnemyModeRelaunchArmed;
		}
		float dx = env->player_pos[0] - enemy->pos_x;
		float dy = env->player_pos[1] - enemy->pos_y;
		float aim;
		if (dy == 0.0f && dx == 0.0f) {
			aim = kRelaunchHalfPi;
		} else {
			aim = (float)atan2((double)dy, (double)dx);
		}
		enemy->angle = env->normalize_sum(aim, enemy->angle_offset);
		speed = enemy->relaunch_speed;
		enemy->speed = speed;
		RegisterClock(&enemy->clock, env->frame_scale);
		enemy->clock.clock.frame = 0;
		enemy->clock.clock.timer = 0.0f;
		enemy->clock.clock.previous = -1;
	}
	env->set_velocity(enemy->velocity, enemy->angle, speed);

	float control = *enemy->clock.clock.control;
	enemy->clock.clock.previous = enemy->clock.clock.frame;
	if (env->clock_env.span_low < control && control < env->clock_env.span_high) {
		enemy->clock.clock.timer += env->clock_env.frame_step;
		enemy->clock.clock.frame += 1;
	} else {
		enemy->clock.clock.timer += control;
		enemy->clock.clock.frame =
		    (int)env->clock_env.float_to_long(enemy->clock.clock.timer);
	}
}
