#pragma once
// The thirty-five-word block 0x004132A0 clears and publishes through
// data_00477708, and its teardown (0x00413300, 0x004133F0).
#include "th10/game/scheduler_remove_locked.hpp"

struct PublishedBlock {
    unsigned int flags;                    // +0x00
    unsigned int words[2];                 // +0x04
    SchedulerTask* task;                   // +0x0C

    void Shutdown();
    void Release();
    PublishedBlock* Destroy(unsigned int flags);
};

extern "C" PublishedBlock* data_00477708;

// Remove the block's scheduler task under the scheduler lock and unpublish it.
__forceinline void PublishedBlock::Shutdown() {
    RemoveScheduledTask(task);
    data_00477708 = 0;
}
