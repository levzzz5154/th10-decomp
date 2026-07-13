#include "th10/util/runtime_pool.hpp"

extern "C" void __cdecl _free(void* memory);

// 0x004388F0 - Clear every allocation slot and the active flag.
RuntimeAllocationPool* __fastcall RuntimeAllocationPool_Initialize(
        void* unused, RuntimeAllocationPool* pool) {
    (void)unused;
    for (uint32_t index = 0; index < 0x2801; ++index) {
        ((uint32_t*)pool)[index] = 0;
    }
    pool->has_allocations = 0;
    return pool;
}

// 0x00438910 and the matching inlined GameMain shutdown path.
void RuntimeAllocationPool_ReleaseAll(RuntimeAllocationPool* pool) {
    if (pool->has_allocations != 0) {
        for (uint32_t index = 0; index < 0x2800; ++index) {
            if (pool->allocations[index] != 0) {
                _free((void*)(unsigned long)pool->allocations[index]);
                pool->allocations[index] = 0;
            }
        }
    }
    pool->has_allocations = 0;
}
