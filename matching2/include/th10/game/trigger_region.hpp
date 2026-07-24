#pragma once

// Trigger region rotation and activation-band classification (retail 0x004267F0).
#include "th10/math/oriented_rect.hpp"

// --- 0x004267F0: stage trigger region classification ------------------------
struct TriggerRegion {
	OrientedRectVec2 position;
	float half_width;
	float half_height;
	int mode;
	int cooldown;
};

struct TriggerRegionEnv {
	float half_extent_factor;
	float negative_half_extent_factor;
	float outer_upper_factor;
	float outer_lower_factor;
	bool trigger_suppressed;
	void (*activate)(TriggerRegion* region);
};

// Returns 1 when the inner region activates, 2 in the outer transition band,
// and 0 otherwise, matching the retail classifier.
int TriggerRegion_Classify(TriggerRegion* region,
                           const OrientedRectVec2* origin, float angle,
                           float vertical_extent, float horizontal_limit,
                           TriggerRegionEnv* env);
