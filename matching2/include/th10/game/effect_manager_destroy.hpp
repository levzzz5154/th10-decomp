#pragma once

#include <cstdint>

// Effect-manager teardown fragment (retail offsets in comments).
struct EffectManagerTasks {
    void* update_task;  // +0x08, scheduler task from construction
    void* render_task;  // +0x0C
    void* buffer;       // +0x370, freed heap block
};

// 0x0042B570 - Tear down the effect manager: release both scheduler
// tasks under the shared scheduler critical section (retail 0x00492274,
// with the reentrancy byte at 0x0049231C bumped around the release,
// which retail routes through FUN_00449F60 with the token from
// 0x00491BE4), clear the published instance global at 0x00477840, and
// free the heap block at +0x370. The retail SEH frame registration
// carries no observable effect and is dropped.
void EffectManager_ReleaseTasks(EffectManagerTasks* state,
                                void (*release_task)(void* task,
                                                     uint32_t token));
