#pragma once

#include "th10/util/scalars.hpp"

// Shared embedded frame clock scaffolding used by recovered translation units.

// Shared frame-clock shapes (same retail layout as earlier batches).
struct FrameClock {
	int previous;
	int frame;
	float timer;
	float* control;
};

struct ClockEnv {
	float span_low;
	float span_high;
	float frame_step;
	long long (*float_to_long)(float value);
};

struct RegisteredClock {
	FrameClock clock;
	Word flags; // bit 0: registered
};
