// Readable reconstruction of the retail 16-bit linear-congruential generator.
// Every step transforms the state through ((seed ^ 0x9630) - 0x6553) followed
// by a multiply-and-fold step (value * 4 + (value >> 14)), all modulo 2^16.
// Callers pass the global state at 0x004918B0 explicitly; the animation
// interpreter (0x0043EE30), enemy-script helpers, and gameplay leaves share it.
#include "th10/math/rng.hpp"

extern float _DAT_00470b98;  // 2^32, added by the x87 unsigned-conversion path
extern float _DAT_00470bec;  // 2^-31
extern float _DAT_00470bf0;  // 2^-32
extern float _DAT_00470afc;  // 1.0f


namespace {

// One 16-bit LCG step shared by all four retail entry points.
uint32_t Rng_Step(uint32_t value) {
    value = ((value ^ 0x9630u) - 0x6553u) & 0xFFFFu;
    return (value * 4u + (value >> 0x0E)) & 0xFFFFu;
}

// Retail converts the 32-bit result through the x87 signed-integer load:
// negative values gain 2^32, producing an exact unsigned conversion before
// the power-of-two scale. Computing in double reproduces the single final
// rounding of the FPU store.
double Rng_ToUnsignedDouble(uint32_t value) {
    double wide = (double)(int32_t)value;
    if ((int32_t)value < 0)
        wide += _DAT_00470b98;
    return wide;
}

} // namespace

// 0x0044B9E0 - Advance the generator twice and return both 16-bit outputs
// packed as (first << 16) | second. The generation counter increases by 2.
uint32_t Rng_NextU32(RngState* state) {
    uint32_t first = Rng_Step(state->seed);
    uint32_t second = Rng_Step(first);
    state->seed = (uint16_t)second;
    state->generation += 2;
    return (first << 16) | second;
}

// 0x0044BA80 - Advance the generator four times but return only the first
// pair of outputs. Equivalent to calling Rng_NextU32 twice and keeping the
// first result; retail bumps the generation counter by 4. No retail caller
// remains, so this documents the complete generator family.
uint32_t Rng_NextU32DoubleStep(RngState* state) {
    uint32_t first = Rng_Step(state->seed);
    uint32_t second = Rng_Step(first);
    uint32_t third = Rng_Step(second);
    uint32_t fourth = Rng_Step(third);
    state->seed = (uint16_t)fourth;
    state->generation += 4;
    return (first << 16) | second;
}

// 0x0044BB20 - Uniform float in [0, 1) from the next 32-bit output.
float Rng_NextFloat(RngState* state) {
    return (float)(Rng_ToUnsignedDouble(Rng_NextU32(state)) * _DAT_00470bf0);
}

// 0x0044BB90 - Uniform float in [-1, 1) from the next 32-bit output.
float Rng_NextFloatSigned(RngState* state) {
    return (float)(Rng_ToUnsignedDouble(Rng_NextU32(state)) * _DAT_00470bec -
                   _DAT_00470afc);
}
