#pragma once

#include "th10/game/entity.hpp"

struct DatCryptParams {
    uint8_t key;
    uint8_t step;
    uint32_t block_size;
    uint32_t byte_limit;
};

extern const DatCryptParams g_dat_crypt_params[8];

uint8_t Dat_GetCryptParamIndex(const char* filename);
const DatCryptParams* Dat_GetCryptParams(const char* filename);

// Clean conventional-ABI form of retail 0x0044B0D0. The original receives
// key in AL and the other five values on the stack.
uint8_t* __stdcall Dat_Decrypt(
    uint8_t* data,
    uint32_t size,
    uint8_t key,
    uint8_t step,
    uint32_t block_size,
    uint32_t byte_limit);
