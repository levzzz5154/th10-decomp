#pragma once
#include "th10/game/scheduler.hpp"
inline void InitializeCallbackLink(TaskLink& link, SchedulerTask* task) {
    link.task = task;
    link.next = 0;
    link.previous = 0;
}
// Allocation view of SchedulerTask with direct access to the whole flag word.
struct CallbackTask {
    int priority;
    unsigned int flags;
    TaskRoutine on_tick;
    TaskRoutine on_register;
    TaskRoutine on_remove;
    TaskLink link;
    void* context;
    CallbackTask() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
        priority = 0;
        flags &= ~1u;
        InitializeCallbackLink(link, reinterpret_cast<SchedulerTask*>(this));
    }
};
typedef char CallbackTask_size_must_match[sizeof(CallbackTask) == sizeof(SchedulerTask) ? 1 : -1];

