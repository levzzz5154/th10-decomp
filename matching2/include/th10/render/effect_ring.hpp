// =============================================================================
// effect_ring.hpp - Water-ring effect initialisation (retail 0x004452F0)
// =============================================================================
#ifndef TH10_RENDER_EFFECT_RING_HPP
#define TH10_RENDER_EFFECT_RING_HPP

enum { EFFECT_RING_SEGMENTS = 0x1F };

// Per-segment record: seven floats (retail stride 7 dwords).
struct EffectRingSegment {
    float direction[2]; // unit polar sample scaled by 0.5
    float jitter[2];    // xorshift noise clamped to +/- 0.06666667
    float phase;        // running angle, wraps at 2*pi
    float amplitude;
    float reserved;
};

struct EffectRingState {
    EffectRingSegment segments[EFFECT_RING_SEGMENTS];
    float base_speed[2]; // two rng samples scaled by _DAT_00470C7C
};

struct EffectRingHooks {
    void* context;
    void* (*alloc)(void* context, unsigned int size); // malloc(0x4B0)
    float (*rand_float)(void* context);               // 0x0044BB90 [0,1)
    unsigned int (*rand_u16)(void* context);          // inline xorshift
    void (*polar_sample)(void* context, float radius, float* out_xy);
    void (*bind_callbacks)(void* context, void* ring); // +0x398/+0x39C
    float angle_step;   // _DAT_00470B6C
    float speed_scale;  // _DAT_00470C7C
};

EffectRingState* EffectRing_Create(const EffectRingHooks* hooks);

#endif // TH10_RENDER_EFFECT_RING_HPP
