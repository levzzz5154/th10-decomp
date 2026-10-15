#pragma once
#include "th10/game/scheduler.hpp"
#include "th10/math/timer.hpp"

// The manager suffix is recovered from 0x004089C0 and its sole caller.
struct CardTasks_004089c0 {
    unsigned char reserved_00[8];
    SchedulerTask* primary_task;                   // +0x0008
    SchedulerTask* secondary_task;                 // +0x000c
    unsigned char reserved_10[0x3734 - 0x10];
    FrameTimer frame_timer;                        // +0x3734
    unsigned char reserved_3748[0x37ac - 0x3748];
    SchedulerTask* trailing_task;                  // +0x37ac

    __declspec(noinline) int InitializeTasks();
};

typedef char CardTasks_size[
    sizeof(CardTasks_004089c0) == 0x37b0 ? 1 : -1];
typedef char CardTasks_primary[
    offsetof(CardTasks_004089c0, primary_task) == 8 ? 1 : -1];
typedef char CardTasks_secondary[
    offsetof(CardTasks_004089c0, secondary_task) == 12 ? 1 : -1];
typedef char CardTasks_timer[
    offsetof(CardTasks_004089c0, frame_timer) == 0x3734 ? 1 : -1];
typedef char CardTasks_trailing[
    offsetof(CardTasks_004089c0, trailing_task) == 0x37ac ? 1 : -1];
