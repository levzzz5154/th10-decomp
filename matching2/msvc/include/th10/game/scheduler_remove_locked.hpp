#pragma once
// The lock-and-remove sequence most teardown code inlines instead of calling
// FuncCtrl_RemoveLocked (0x00449F20): take the scheduler lock, bump its
// depth byte, remove the task from the game's scheduler and release both.
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"

extern "C" FuncCtrl* g_func_ctrl;  // the game's scheduler

__forceinline void RemoveScheduledTask(SchedulerTask* task) {
    FuncCtrl* scheduler = g_func_ctrl;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// A pair of tasks registered together (primary and secondary callbacks).
struct SchedulerTaskPair {
    unsigned char unknown_000[8];
    SchedulerTask* primary;    // +0x08
    SchedulerTask* secondary;  // +0x0C
};

__forceinline void RemoveScheduledTaskPair(SchedulerTaskPair* pair) {
    RemoveScheduledTask(pair->primary);
    RemoveScheduledTask(pair->secondary);
}
