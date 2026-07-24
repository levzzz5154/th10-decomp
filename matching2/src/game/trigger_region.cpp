#include "th10/game/trigger_region.hpp"
#include "th10/math/oriented_rect.hpp"

#include <cmath>

// 0x004267F0 - rotates the region position around the supplied origin, then
// classifies it against an inner activation rectangle and an asymmetric outer
// transition band. Eligible inner hits invoke the activation path once.
int TriggerRegion_Classify(TriggerRegion* region,
                           const OrientedRectVec2* origin, float angle,
                           float vertical_extent, float horizontal_limit,
                           TriggerRegionEnv* env) {
	const float dx = region->position.x - origin->x;
	const float dy = region->position.y - origin->y;
	const float sine = std::sin(-angle);
	const float cosine = std::cos(-angle);
	const float local_x = dx * cosine - sine * dy;
	const float local_y = sine * dx + cosine * dy;

	const float left = local_x - region->half_width;
	const float right = local_x + region->half_width;
	const float lower = local_y - region->half_height;
	const float upper = local_y + region->half_height;
	if (left <= horizontal_limit) {
		const bool outside_inner =
		    vertical_extent * env->half_extent_factor < lower ||
		    right < 0.0f ||
		    upper < vertical_extent * env->negative_half_extent_factor;
		if (!outside_inner) {
			if (!env->trigger_suppressed && region->mode != 2 &&
			    region->mode != 3 && region->mode != 4 &&
			    region->cooldown < 1) {
				env->activate(region);
				return 1;
			}
		} else if (0.0f <= right &&
		           lower <= vertical_extent * env->outer_upper_factor &&
		           vertical_extent * env->outer_lower_factor <= lower) {
			return 2;
		}
	}
	return 0;
}
