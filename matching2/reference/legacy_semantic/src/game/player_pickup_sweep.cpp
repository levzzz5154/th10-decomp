#include "th10/game/player_pickup_sweep.hpp"

#include <cmath>

namespace {
bool Overlap(float a_min, float a_max, float b_min, float b_max) {
	return a_min <= b_max && a_max >= b_min;
}

bool PickupOverlaps(const Pickup& pickup,
                    const PickupDescriptor& descriptor,
                    const float center[2], const float size[2]) {
	const float player_left = center[0] - size[0] * 0.5f;
	const float player_right = center[0] + size[0] * 0.5f;
	const float player_top = center[1] - size[1] * 0.5f;
	const float player_bottom = center[1] + size[1] * 0.5f;
	const float pickup_left = pickup.position[0] - descriptor.width * 0.5f;
	const float pickup_right = pickup.position[0] + descriptor.width * 0.5f;
	const float pickup_top = pickup.position[1] - descriptor.height * 0.5f;
	const float pickup_bottom = pickup.position[1] + descriptor.height * 0.5f;
	if (!Overlap(pickup_left, pickup_right, player_left, player_right) ||
	    !Overlap(pickup_top, pickup_bottom, player_top, player_bottom))
		return false;
	// Type 3 tests the player's lower edge; all other types test the pickup's
	// upper edge. This asymmetry is explicit in the retail branch.
	return descriptor.type == 3 ? player_bottom >= 0.0f : pickup_top >= 0.0f;
}

bool RegionOverlaps(const PickupCollisionRegion& region,
                    const float center[2], const float size[2]) {
	if ((region.flags & 2u) != 0) {
		const float dx = region.center[0] - center[0];
		const float dy = region.center[1] - center[1];
		return dx * dx + dy * dy <= region.radius * region.radius;
	}
	const float half_player_x = size[0] * 0.5f;
	const float half_player_y = size[1] * 0.5f;
	float local_x;
	float local_y;
	if (region.angle == 0.0f) {
		local_x = center[0] - region.center[0];
		local_y = center[1] - region.center[1];
	} else {
		const float dx = center[0] - region.center[0];
		const float dy = center[1] - region.center[1];
		const float sine = (float)std::sin(-region.angle);
		const float cosine = (float)std::cos(-region.angle);
		local_x = cosine * dx - sine * dy;
		local_y = sine * dx + cosine * dy;
	}
	return local_x + half_player_x >= region.width * -0.5f &&
	       local_x - half_player_x <= region.width * 0.5f &&
	       local_y + half_player_y >= region.height * -0.5f &&
	       local_y - half_player_y <= region.height * 0.5f;
}
} // namespace

// 0x00428630 - pickup and score-field collision sweep.
int Player_CollectAndScoreFields(int* optional_result, PickupManager* manager,
                                 const float player_center[2],
                                 const float player_size[2],
                                 const PickupSweepEnv* env) {
	if (manager->generation_end == manager->generation_begin)
		return 0;
	if (optional_result)
		*optional_result = 0;

	int total = 0;
	for (int i = 0; i < 128; ++i) {
		Pickup& pickup = manager->pickups[i];
		if (pickup.state == 0 || pickup.state == 2 || !pickup.descriptor)
			continue;
		PickupDescriptor& descriptor = *pickup.descriptor;
		if (!PickupOverlaps(pickup, descriptor, player_center, player_size))
			continue;
		if (descriptor.filter &&
		    descriptor.filter(manager, &pickup, player_center) != 0)
			continue;

		if (!pickup.initialized) {
			env->stop_animation(&pickup, &descriptor);
			pickup.initialized = 1;
		}
		pickup.collected = 1;
		if (descriptor.type != 3 || env->interval_test(&pickup, 4) != 0)
			total += descriptor.value;

		if (descriptor.type != 3) {
			const int saved = env->read_animation_field(pickup.animation_handle);
			env->retire_animation(&pickup);
			pickup.animation_handle = env->create_animation(
			    manager->animation_resource, descriptor.collected_script + 5, 15);
			env->write_animation_field(pickup.animation_handle, saved);
			env->or_animation_flags(pickup.animation_handle, 4u);
			pickup.transition_scale = 0.1f;
			pickup.state = 2;
			pickup.velocity_scale *= 0.125f;
		}
		if (descriptor.type == 2) {
			env->spawn_indicator(descriptor.value, manager, pickup.position,
			                     32.0f, 1.4f, 13, descriptor.value / 3);
		}
	}

	total += env->player_hit_test();
	for (int i = 0; i < 32; ++i) {
		PickupCollisionRegion& region = manager->regions[i];
		if ((region.flags & 1u) == 0)
			continue;
		if (region.current_frame != region.previous_frame &&
		    region.current_frame % region.interval == 0)
			continue;
		if (!RegionOverlaps(region, player_center, player_size))
			continue;
		total += region.value;
		region.accumulated += region.value;
		if (region.accumulated >= region.limit)
			region.value = 0;
	}

	if (total != 0) {
		*env->score += (total / 10 + 10) / 10;
		if (*env->score >= 1000000000)
			*env->score = 999999999;
	}
	return total;
}
