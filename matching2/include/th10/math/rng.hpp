#pragma once

// MSVC 7.1 is pre-C++11 — use manual typedefs instead of <cstdint>
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef int            int32_t;

// Linear-congruential generator state used by the retail RNG entry points at
// 0x0044B9E0 through 0x0044BC10. Callers pass the global instance at
// 0x004918B0 explicitly, so the clean API takes the state as an argument.
// The retail record is the two-word block: 16-bit seed at +0x00 and the 32-bit
// generation counter at +0x04.
struct RngState {
    uint16_t seed;
    uint16_t reserved_02;
    uint32_t generation; // retail ADD wraps modulo 2^32
};

uint32_t Rng_NextU32(RngState* state);
uint32_t Rng_NextU32DoubleStep(RngState* state);
float    Rng_NextFloat(RngState* state);
float    Rng_NextFloatSigned(RngState* state);
