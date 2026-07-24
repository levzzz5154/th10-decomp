#pragma once

// Effect acceleration step (retail 0x0041D2C0).
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

struct AccelEffect {
	FrameClock clock;
	float velocity[3];
	float angle;
	float aux;
	float aux_accel;
	float accel[3];
	int duration;
	Word flags; // bit 4 cleared on expiry
};

void Effect_AccelStep(AccelEffect* fx, float frame_scale,
                      float min_component, const ClockEnv* clock_env);
