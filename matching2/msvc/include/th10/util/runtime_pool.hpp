#pragma once

#include "th10/game/entity.hpp"

// Process-lifetime allocation registry created at the start of GameMain.
// The flag is set once entries need individual cleanup during shutdown.
struct RuntimeAllocationPool {
    uint32_t allocations[0x2800]; // +0x0000 .. +0x9FFF (32-bit pointers)
    uint32_t has_allocations;   // +0xA000
};
// sizeof(RuntimeAllocationPool) == 0xA004

RuntimeAllocationPool* __fastcall RuntimeAllocationPool_Initialize(
    void* unused, RuntimeAllocationPool* pool);
void RuntimeAllocationPool_ReleaseAll(RuntimeAllocationPool* pool);

