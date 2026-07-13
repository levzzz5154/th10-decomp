#pragma once

#include "th10/game/entity.hpp"

// TH10's 0x2000-byte sliding-window decoder (retail 0x00435DC0).
// If output is null, the function allocates output_size bytes with malloc.
uint8_t* __stdcall Dat_LzssDecompress(
    const uint8_t* input,
    int32_t input_size,
    uint8_t* output,
    uint32_t output_size);
