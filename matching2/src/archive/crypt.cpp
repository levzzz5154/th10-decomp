#include "th10/archive/crypt.hpp"

extern "C" void* __cdecl _malloc(uint32_t size);
extern "C" void __cdecl _free(void* memory);

const DatCryptParams g_dat_crypt_params[8] = {
    {0x1B, 0x37, 0x0040, 0x2800},
    {0x51, 0xE9, 0x0040, 0x3000},
    {0xC1, 0x51, 0x0080, 0x3200},
    {0x03, 0x19, 0x0400, 0x7800},
    {0xAB, 0xCD, 0x0200, 0x2800},
    {0x12, 0x34, 0x0080, 0x3200},
    {0x35, 0x97, 0x0080, 0x2800},
    {0x99, 0x37, 0x0400, 0x2000},
};

uint8_t* __stdcall Dat_Decrypt(
        uint8_t* data,
        uint32_t size,
        uint8_t key,
        uint8_t step,
        uint32_t block_size,
        uint32_t byte_limit) {
    uint32_t remainder = size % block_size;
    uint32_t processed_size = size;
    if (remainder < block_size / 4) {
        processed_size -= remainder;
    }
    processed_size -= processed_size & 1;

    uint32_t temporary_size = size < byte_limit ? size : byte_limit;
    uint8_t* temporary = (uint8_t*)_malloc(temporary_size);
    if (!temporary) {
        return data;
    }

    for (uint32_t index = 0; index < temporary_size; ++index) {
        temporary[index] = data[index];
    }

    uint8_t* source = temporary;
    uint8_t* destination = data;
    uint32_t remaining = processed_size;
    uint32_t limit_remaining = byte_limit;

    while (remaining > 0 && limit_remaining > 0) {
        uint32_t chunk = remaining < block_size ? remaining : block_size;
        uint8_t* destination_end = destination + chunk;

        uint8_t* odd_destination = destination_end - 1;
        uint32_t odd_count = (chunk + 1) / 2;
        for (uint32_t index = 0; index < odd_count; ++index) {
            *odd_destination = *source++ ^ key;
            odd_destination -= 2;
            key = (uint8_t)(key + step);
        }

        uint8_t* even_destination = destination_end - 2;
        uint32_t even_count = chunk / 2;
        for (uint32_t index = 0; index < even_count; ++index) {
            *even_destination = *source++ ^ key;
            even_destination -= 2;
            key = (uint8_t)(key + step);
        }

        destination = destination_end;
        remaining -= chunk;
        limit_remaining -= chunk;
    }

    _free(temporary);
    return data;
}
