// UNSELECTED: complete 151-byte native body differs in nine bytes.
// See recovery_notes/frame_counter_resume_00413350_2026_10_02.md.
// 0x00413350: create the frame-rate counter.
//
// The 0x8C-byte counter is cleared, flagged and published through
// data_00477708; a scheduler task then draws it every frame at priority 0x2F
// of the secondary chain, and the counter keeps the task.
#include "th10/game/published_block.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/app/frame_rate_counter_native.hpp"

int __fastcall FpsDrawCallback_00413690(FrameRateCounter_004134b0* counter);

void* __cdecl operator new(unsigned int size);
extern "C" void* __cdecl memset(void* destination, int value, unsigned int size);
extern "C" Scheduler* data_00491be4;

// The whole counter; its constructor clears and publishes it.
struct FrameRateCounterBlock_00413350 : PublishedBlock {
    unsigned int rest[31];

    FrameRateCounterBlock_00413350() {
        memset(this, 0, sizeof(FrameRateCounterBlock_00413350));
        flags |= 2;
        data_00477708 = this;
    }
};

typedef char FrameRateCounterBlock_00413350_size_must_be_8c[
    sizeof(FrameRateCounterBlock_00413350) == 0x8C ? 1 : -1];

// The 0x24-byte scheduler task as its constructor leaves it.
struct CounterDrawTask_00413350 {
    int priority;                          // +0x00
    unsigned int heap_owned : 1;           // +0x04
    unsigned int enabled : 1;
    unsigned int reserved_flags : 30;
    void* on_tick;                         // +0x08
    void* on_register;                     // +0x0C
    void* on_remove;                       // +0x10
    void* link_task;                       // +0x14
    void* link_next;                       // +0x18
    void* link_previous;                   // +0x1C
    void* context;                         // +0x20

    CounterDrawTask_00413350() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
        priority = 0;
        heap_owned = priority;
        link_task = this;
        link_next = 0;
        link_previous = 0;
    }
};

// 0x00449ED0 inline: a heap-owned task around a callback.
static __forceinline CounterDrawTask_00413350* CreateCallbackTask(void* callback) {
    CounterDrawTask_00413350* task = new CounterDrawTask_00413350;
    task->heap_owned = 1;
    task->on_tick = callback;
    task->on_register = 0;
    task->on_remove = 0;
    return task;
}

#pragma code_seg(".text$00d_chrf_fps")
PublishedBlock* __cdecl PublishedBlock_Create_00413350() {
    PublishedBlock* counter = new FrameRateCounterBlock_00413350;
    CounterDrawTask_00413350* task = CreateCallbackTask((void*)&FpsDrawCallback_00413690);
    task->context = counter;
    task->enabled = 1;
    Scheduler_RegisterSecondary(data_00491be4, (SchedulerTask*)task, 0x2F);
    counter->task = (SchedulerTask*)task;
    return counter;
}
#pragma code_seg()
