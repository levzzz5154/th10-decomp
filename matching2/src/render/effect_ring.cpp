// =============================================================================
// effect_ring.cpp - Water-ring effect initialisation
// =============================================================================
#include "th10/render/effect_ring.hpp"

// 0x004452F0 - EffectRing_Create: allocate the 0x4B0-byte ring buffer bound
// at vm+0x358, seed the two base-speed samples, then fill all 0x1F segments
// with polar direction samples plus xorshift jitter clamped to 1/15, walking
// the phase by the fixed angle step and wrapping at 2*pi.
EffectRingState* EffectRing_Create(const EffectRingHooks* hooks) {
    EffectRingState* ring = static_cast<EffectRingState*>(
        hooks->alloc(hooks->context, 0x4B0));
    if (ring == 0)
        return 0;
    hooks->bind_callbacks(hooks->context, ring);

    ring->base_speed[0] = hooks->rand_float(hooks->context) *
                          hooks->speed_scale;
    ring->base_speed[1] = hooks->rand_float(hooks->context) *
                          hooks->speed_scale;

    const float kTwoPi = 6.2831853f;
    const float kJitterClamp = 0.06666667f;
    float angle = 0.0f;
    for (int segment = 0; segment < EFFECT_RING_SEGMENTS; ++segment) {
        EffectRingSegment* out = &ring->segments[segment];
        hooks->polar_sample(hooks->context, 0.5f, out->direction);
        for (int axis = 0; axis < 2; ++axis) {
            // Inline retail xorshift: ((u16 ^ 0x9630) + 0x9AAD) rotated,
            // normalised into [-clamp, clamp].
            unsigned int raw = hooks->rand_u16(hooks->context);
            unsigned int mixed = ((raw ^ 0x9630u) + 0x9AADu) & 0xFFFFu;
            float centered =
                (static_cast<float>(mixed) / 32768.0f) - 1.0f;
            float jitter = centered * kJitterClamp;
            if (jitter > kJitterClamp) jitter = kJitterClamp;
            if (jitter < -kJitterClamp) jitter = -kJitterClamp;
            out->jitter[axis] = jitter;
        }
        out->phase = angle;
        out->amplitude = 0.0f;
        out->reserved = 0.0f;
        angle += hooks->angle_step;
        if (angle >= kTwoPi)
            angle -= kTwoPi;
    }
    return ring;
}
