#include "th10/archive/crypt.hpp"

// Historical model. The signed byte-limit stopping condition is corrected
// and retail-tested in reference/semantic_candidates/dat_crypt.cpp; see
// recovery_notes/dat_crypt_0044b0d0_0044b220.md before reusing these bodies.

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

// The content cipher row is selected by the low three bits of an 8-bit sum
// over the complete archive filename (the loop at 0x00434E54).
uint8_t Dat_GetCryptParamIndex(const char* filename) {
    uint8_t sum = 0;
    while (*filename != 0) {
        sum = (uint8_t)(sum + (uint8_t)*filename++);
    }
    return sum & 7;
}

const DatCryptParams* Dat_GetCryptParams(const char* filename) {
    return &g_dat_crypt_params[Dat_GetCryptParamIndex(filename)];
}

// Shared scaffolding of the two retail codec leaves. The processed prefix
// length is a signed quantity: an odd size whose remainder falls below one
// quarter of the block produces -1, which skips the chunk loop entirely.
static int32_t Dat_ProcessedPrefixSize(
        uint32_t size, uint32_t block_size) {
    uint32_t remainder = size % block_size;
    int32_t processed_size = (int32_t)(size - (size & 1));
    if (remainder < block_size / 4) {
        processed_size -= (int32_t)remainder;
    }
    return processed_size;
}

static uint8_t* Dat_MakeSnapshot(
        const uint8_t* data, uint32_t size, uint32_t byte_limit) {
    uint32_t temporary_size = size < byte_limit ? size : byte_limit;
    uint8_t* temporary = (uint8_t*)_malloc(temporary_size);
    if (!temporary) {
        return 0;
    }
    for (uint32_t index = 0; index < temporary_size; ++index) {
        temporary[index] = data[index];
    }
    return temporary;
}

// 0x0044B0D0 - Decode one interleaved XOR layer in place. Sequentially read
// snapshot bytes are folded back over each chunk so the odd slots receive
// the first half and the even slots the second, each byte XORed with the
// rolling key.
uint8_t* __stdcall Dat_Decrypt(
        uint8_t* data,
        uint32_t size,
        uint8_t key,
        uint8_t step,
        uint32_t block_size,
        uint32_t byte_limit) {
    int32_t remaining = Dat_ProcessedPrefixSize(size, block_size);
    uint8_t* temporary = Dat_MakeSnapshot(data, size, byte_limit);
    if (!temporary) {
        return data;
    }

    uint8_t* source = temporary;
    uint8_t* destination = data;
    uint32_t limit_remaining = byte_limit;

    while (remaining > 0 && limit_remaining > 0) {
        uint32_t chunk =
            (uint32_t)remaining < block_size ? (uint32_t)remaining : block_size;
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
        remaining -= (int32_t)chunk;
        limit_remaining -= chunk;
    }

    _free(temporary);
    return data;
}

// 0x0044B220 - Encode one interleaved XOR layer in place; the exact inverse
// of the decode leaf. Each chunk reads the snapshot's odd and even slots in
// descending order and writes them out sequentially with the rolling key.
uint8_t* __stdcall Dat_Encrypt(
        uint8_t* data,
        uint32_t size,
        uint8_t key,
        uint8_t step,
        uint32_t block_size,
        uint32_t byte_limit) {
    int32_t remaining = Dat_ProcessedPrefixSize(size, block_size);
    uint8_t* temporary = Dat_MakeSnapshot(data, size, byte_limit);
    if (!temporary) {
        return data;
    }

    uint8_t* chunk_base = temporary;
    uint8_t* destination = data;
    uint32_t limit_remaining = byte_limit;

    while (remaining > 0 && limit_remaining > 0) {
        uint32_t chunk =
            (uint32_t)remaining < block_size ? (uint32_t)remaining : block_size;

        const uint8_t* odd_source = chunk_base + chunk - 1;
        uint32_t odd_count = (chunk + 1) / 2;
        for (uint32_t index = 0; index < odd_count; ++index) {
            *destination++ = *odd_source ^ key;
            odd_source -= 2;
            key = (uint8_t)(key + step);
        }

        const uint8_t* even_source = chunk_base + chunk - 2;
        uint32_t even_count = chunk / 2;
        for (uint32_t index = 0; index < even_count; ++index) {
            *destination++ = *even_source ^ key;
            even_source -= 2;
            key = (uint8_t)(key + step);
        }

        chunk_base += chunk;
        remaining -= (int32_t)chunk;
        limit_remaining -= chunk;
    }

    _free(temporary);
    return data;
}
