#pragma once

#include <cstdint>

// Scheduler task node allocated next to the stats manager (retail
// 32-bit word offsets in comments).
struct StatsTaskNode {
    uint32_t state0;      // word 0, cleared
    uint32_t flags;       // word 1, bit 0 cleared then bits 0-1 set
    void* callback;       // word 2, retail LAB_00413690
    uint32_t reserved_3;  // word 3, cleared
    uint32_t reserved_4;  // word 4, cleared
    StatsTaskNode* self;  // word 5
    uint32_t reserved_6;  // word 6, cleared
    uint32_t reserved_7;  // word 7, cleared
    uint32_t* owner;      // word 8, the stats manager
};

// 0x00413350 - Create the 0x8C-byte gameplay stats manager and its
// scheduler task: zero the manager, set constructed bit 1, publish it
// through the retail global at 0x00477708, allocate and wire the
// 0x24-byte task node (callback, self, owner, flag bits 0-1), register
// it with the scheduler token (retail global 0x00491BE4), and store the
// node in the manager's word 3 (with retail 32-bit truncation on the
// host). The allocator, the scheduler registration (retail 0x00449B70),
// and the task callback are injected. Retail would dereference a failed
// node allocation; the readable form returns the manager early instead.
uint32_t* GameplayStats_CreateAndRegister(
    void* (*allocate)(uint32_t size),
    void (*register_task)(uint32_t token), void* task_callback);
