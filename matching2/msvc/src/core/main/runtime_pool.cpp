#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// Recovered semantic C++ definitions.
#include "th10/util/runtime_pool.hpp"

RuntimeAllocationPool* __fastcall RuntimeAllocationPool_Initialize(
        void* unused, RuntimeAllocationPool* pool) {
    (void)unused;
    for (uint32_t index = 0; index < 0x2801; ++index)
        ((uint32_t*)pool)[index] = 0;
    pool->has_allocations = 0;
    return pool;
}

