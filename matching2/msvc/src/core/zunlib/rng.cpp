#include "th10/math/rng.hpp"
#include <string.h>

// 0x0044B9E0 - Pack two generated words, first in the high half.
unsigned int __fastcall Rng_NextU32(RngState* state) {
    unsigned short first = state->NextWord();
    unsigned short second = state->NextWord();
    return second | (static_cast<unsigned int>(first) << 16);
}

// 0x0044BA30 - A second retail entry with the same recurrence and packing.
// The bytes establish identical behavior; its original API name is unknown.
unsigned int __fastcall Rng_NextU32Alternate(RngState* state) {
    return Rng_NextU32(state);
}

// 0x0044BA80 - Advance four words and return the first pair in little-endian
// memory order. This places the first word in the low half, unlike NextU32.
unsigned int __fastcall Rng_NextU32DoubleStep(RngState* state) {
    unsigned short words[4];
    words[0] = state->NextWord();
    words[1] = state->NextWord();
    words[2] = state->NextWord();
    words[3] = state->NextWord();
    unsigned int result;
    memcpy(&result, words, sizeof(result));
    return result;
}

// 0x0044BB20 - Scale the next unsigned value by 2^-32.
// MSVC uses an x87 integer load and a 2^32 correction for unsigned conversion.
float __fastcall Rng_NextFloat(RngState* state) {
    return Rng_NextU32(state) * (1.0f / 4294967296.0f);
}

// 0x0044BB90 - Scale by 2^-31 and center around zero.
float __fastcall Rng_NextFloatSigned(RngState* state) {
    return Rng_NextU32(state) * (1.0f / 2147483648.0f) - 1.0f;
}
