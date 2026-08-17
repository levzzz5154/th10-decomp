#include "th10/render/effect_ring_update.hpp"
#include "th10/game/ending_text.hpp"

#include <cmath>
#include <cstring>

namespace {

// Add one full texture period to the u column (all 33 vertices).
void RingWrapU(EffectRingState* ring) {
	for (int i = 0; i < 33; ++i) {
		ring->vertices[i].u += 1.0f; // _DAT_00470AFC
	}
}

// Add one full texture period to the v column (all 33 vertices).
void RingWrapV(EffectRingState* ring) {
	for (int i = 0; i < 33; ++i) {
		ring->vertices[i].v += 1.0f; // _DAT_00470AFC
	}
}

} // namespace

// 0x00445620 - Per-frame update of the 32-segment textured ripple ring:
// pin the center vertex to the owner position (base + offset), scroll every
// vertex's u and v by the ring's scroll speed with a +1.0 column re-wrap
// whenever a coordinate drops below zero, tint the center with the owner
// color and the rim with the same color at alpha zero, grow each rim radius
// by its per-vertex radial speed, place rim vertex k on the circle at angle
// -pi + (k-1) * 2*pi/31 (_DAT_00470B6C step) around the owner, and close the
// fan by duplicating rim vertex 1 into slot 32.
int EffectRing_Update(EffectRingOwner* owner) {
	EffectRingState* ring = owner->ring;
	const float center_x = owner->offset_position[0] + owner->base_position[0];
	const float center_y = owner->offset_position[1] + owner->base_position[1];
	const float center_z = owner->offset_position[2] + owner->base_position[2];
	const float scroll = ring->uv_scroll_speed;

	EffectRingVertex* center = &ring->vertices[0];
	center->x = center_x;
	center->y = center_y;
	center->z = center_z;
	center->u += scroll;
	if (center->u < 0.0f) { // _DAT_00470B04
		RingWrapU(ring);
	}
	center->v += scroll;
	if (center->v < 0.0f) {
		RingWrapV(ring);
	}
	center->diffuse = owner->diffuse; // center keeps the owner alpha

	float angle = -3.1415927f;
	for (int k = 1; k <= 31; ++k) {
		EffectRingVertex* vertex = &ring->vertices[k];
		vertex->u += scroll;
		if (vertex->u < 0.0f) {
			RingWrapU(ring);
		}
		vertex->v += scroll;
		if (vertex->v < 0.0f) {
			RingWrapV(ring);
		}
		vertex->diffuse = owner->diffuse & 0x00FFFFFFu; // rim alpha = 0

		ring->radius[k - 1] += ring->radial_speed[k - 1];
		// Vector2_SetPolar (0x004458B0 hook, already semantic) into x/y,
		// then translate by the owner position.
		vertex->x = std::cos(angle) * ring->radius[k - 1] + center_x;
		vertex->y = std::sin(angle) * ring->radius[k - 1] + center_y;
		// Faithful quirk: the raw body only accumulates the owner Z onto the
		// rim Z each frame and never resets it, so rim Z drifts whenever the
		// owner Z sum is nonzero.
		vertex->z += center_z;
		angle += 0.2026834f; // _DAT_00470B6C = float32(2*pi/31)
	}
	ring->vertices[32] = ring->vertices[1];
	return 0;
}

int EffectRing_Draw(const EffectRingOwner* owner,
                    const EffectRingDrawEnv* env) {
    if (owner == nullptr || owner->ring == nullptr || env == nullptr ||
        env->flush == nullptr || env->sync_state == nullptr ||
        env->bind_texture == nullptr || env->draw_fan == nullptr)
        return -1;
    env->flush(env->context);
    env->sync_state(env->context);
    env->bind_texture(env->context);
    env->flush(env->context);
    env->draw_fan(env->context, 31, owner->ring->vertices,
                  sizeof(EffectRingVertex));
    return 0;
}
