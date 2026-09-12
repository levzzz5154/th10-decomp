#pragma once

#include "th10/game/entity.hpp"

// TH10's 0x2000-byte sliding-window decoder (retail 0x00435DC0).
// If output is null, the function allocates output_size bytes with malloc.
uint8_t* __stdcall Dat_LzssDecompress(
    const uint8_t* input,
    int32_t input_size,
    uint8_t* output,
    uint32_t output_size);

// Reentrant cleaned form of the encoder at 0x004359B0. The returned buffer is
// allocated with malloc and must be released by the caller.
uint8_t* __stdcall Dat_LzssCompress(
    const uint8_t* input,
    int32_t input_size,
    int32_t* output_size);
