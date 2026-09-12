#include "th10/game/effect_accel.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cmath>
#include <cstring>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).
void AdvanceClock(FrameClock* clock, const ClockEnv* env) {
	clock->previous = clock->frame;
	if (env->span_low < *clock->control && *clock->control < env->span_high) {
		clock->timer += env->frame_step;
		clock->frame += 1;
	} else {
		clock->timer += *clock->control;
		clock->frame = (int)env->float_to_long(clock->timer);
	}
}




} // namespace

// 0x0041D2C0 - accelerates an effect while its clock runs: integrates the
// aux value and velocity, re-aims the angle from the velocity when it is
// large enough, then advances the frame clock.
void Effect_AccelStep(AccelEffect* fx, float frame_scale,
                      float min_component, const ClockEnv* clock_env) {
	if (fx->clock.frame < fx->duration) {
		fx->aux += frame_scale * fx->aux_accel;
		fx->velocity[0] += frame_scale * fx->accel[0];
		fx->velocity[1] += frame_scale * fx->accel[1];
		fx->velocity[2] += frame_scale * fx->accel[2];
		float vx = fx->velocity[0];
		float vy = fx->velocity[1];
		float abs_vx = vx < 0.0f ? -vx : vx;
		float abs_vy = vy < 0.0f ? -vy : vy;
		if (min_component < abs_vx || min_component < abs_vy) {
			fx->angle = atan2f(vy, vx);
		}
	} else {
		fx->flags &= ~0x10u;
	}
	AdvanceClock(&fx->clock, clock_env);
}
