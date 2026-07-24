// =============================================================================
// interpolators.cpp - Embedded interpolator ticks used by the ANM VM
// Functions: 0x00404610, 0x00441AD0, 0x00441600, 0x00441950
// =============================================================================
#include "th10/math/interpolators.hpp"

namespace {

float EaseFraction(int mode, float t) {
    // Retail dispatch (FUN_0044C350 family): 0 linear, 1/2/3 accelerating
    // powers, 4/5/6 decelerating powers, 7 hold, 8 bezier handled by the
    // callers, 9+ smooth-step pairs.
    switch (mode) {
    case 1: return t * t;
    case 2: return t * t * t;
    case 3: return t * t * t * t;
    case 4: return 1.0f - (1.0f - t) * (1.0f - t);
    case 5: return 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t);
    case 6: {
        float u = (1.0f - t) * (1.0f - t);
        return 1.0f - u * u;
    }
    case 9: return t < 0.5f ? 2.0f * t * t
                            : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
    default: return t;
    }
}

float BezierPoint(float start, float control_a, float control_b, float end,
                  float t) {
    float u = 1.0f - t;
    return start * u * u * u + 3.0f * control_a * u * u * t +
           3.0f * control_b * u * t * t + end * t * t * t;
}

} // namespace

// 0x00404610 - Interp3F_Tick: advance a three-component float interpolator
// one frame. Mode 7 holds, mode 0x11 integrates acceleration into velocity,
// mode 8 evaluates the cubic bezier through the two control rows, and every
// other mode eases between start and target. Returns 1 while running and 0
// on the completing frame.
int Interp3F_Tick(Interp3F* state) {
    if (state->duration <= 0 && state->mode != 7 && state->mode != 0x11)
        return 0;
    switch (state->mode) {
    case 7: // velocity hold: position integrates velocity forever
        for (int axis = 0; axis < 3; ++axis)
            state->position[axis] += state->velocity[axis] * state->speed;
        state->elapsed += 1;
        return 1;
    case 0x11: // accelerated: velocity integrates the acceleration row
        for (int axis = 0; axis < 3; ++axis) {
            state->velocity[axis] += state->acceleration[axis] * state->speed;
            state->position[axis] += state->velocity[axis] * state->speed;
        }
        state->elapsed += 1;
        return 1;
    default:
        break;
    }
    state->elapsed += 1;
    float t = static_cast<float>(state->elapsed) /
              static_cast<float>(state->duration);
    if (t > 1.0f)
        t = 1.0f;
    if (state->mode == 8) {
        for (int axis = 0; axis < 3; ++axis)
            state->position[axis] = BezierPoint(
                state->start[axis], state->acceleration[axis],
                state->velocity[axis], state->target[axis], t);
    } else {
        float eased = EaseFraction(state->mode, t);
        for (int axis = 0; axis < 3; ++axis)
            state->position[axis] =
                state->start[axis] +
                (state->target[axis] - state->start[axis]) * eased;
    }
    if (state->elapsed >= state->duration) {
        state->duration = 0;
        return 0;
    }
    return 1;
}

// 0x00441AD0 - Interp2F_Tick: two-component float variant (growth vector).
int Interp2F_Tick(Interp2F* state) {
    if (state->duration <= 0)
        return 0;
    state->elapsed += 1;
    float t = static_cast<float>(state->elapsed) /
              static_cast<float>(state->duration);
    if (t > 1.0f)
        t = 1.0f;
    float eased = EaseFraction(state->mode, t);
    for (int axis = 0; axis < 2; ++axis)
        state->value[axis] = state->start[axis] +
                             (state->target[axis] - state->start[axis]) *
                             eased;
    if (state->elapsed >= state->duration) {
        state->duration = 0;
        return 0;
    }
    return 1;
}

// 0x00441600 - Interp3I_Tick: three-component integer interpolator (colour
// channels). The -999999 sentinel skips a channel; mode 8 sums the four
// bezier basis terms with integer rounding (retail FUN_00441E50 calls).
int Interp3I_Tick(Interp3I* state) {
    if (state->duration <= 0)
        return 0;
    state->elapsed += 1;
    float t = static_cast<float>(state->elapsed) /
              static_cast<float>(state->duration);
    if (t > 1.0f)
        t = 1.0f;
    float eased = state->mode == 8 ? t : EaseFraction(state->mode, t);
    for (int axis = 0; axis < 3; ++axis) {
        if (state->target[axis] == INTERP_INT_SENTINEL)
            continue;
        float mixed = static_cast<float>(state->start[axis]) +
                      (static_cast<float>(state->target[axis]) -
                       static_cast<float>(state->start[axis])) * eased;
        state->value[axis] = static_cast<int>(mixed + 0.5f);
    }
    if (state->elapsed >= state->duration) {
        state->duration = 0;
        return 0;
    }
    return 1;
}

// 0x00441950 - Interp1I_Tick: single-channel integer variant (alpha).
int Interp1I_Tick(Interp1I* state) {
    if (state->duration <= 0)
        return 0;
    state->elapsed += 1;
    float t = static_cast<float>(state->elapsed) /
              static_cast<float>(state->duration);
    if (t > 1.0f)
        t = 1.0f;
    float eased = EaseFraction(state->mode, t);
    float mixed = static_cast<float>(state->start) +
                  (static_cast<float>(state->target) -
                   static_cast<float>(state->start)) * eased;
    state->value = static_cast<int>(mixed + 0.5f);
    if (state->elapsed >= state->duration) {
        state->duration = 0;
        return 0;
    }
    return 1;
}
