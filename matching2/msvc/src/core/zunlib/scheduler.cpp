#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"

// 0x00420C00: recovered in build_support/layout/units/music_requests_0b68f8.cpp.

// 0x00421F60: recovered in src/game/mother/game_state_update_frame_maximum.cpp.

// 0x00422C30: recovered in src/game/pause/pause_unpause.cpp.

// 0x0042C730: maintained in src/game/title/title_dispatch_animation_slot.cpp.

// 0x0042C750: maintained in src/game/title/title_dispatch_animation_slot_secondary.cpp.


#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"

struct SchedulerTaskRaw {
    int priority;
    unsigned int flags;
    TaskRoutine on_tick;
    TaskRoutine on_register;
    TaskRoutine on_remove;
    TaskLink link;
    void* context;
};

static SchedulerTaskRaw* raw_task(TaskLink* link) {
    return (SchedulerTaskRaw*)link->task;
}

// 0x00449C00..0x00449D33: primary task pass and compiler switch table.
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RunPrimary(
        FuncCtrl* scheduler) {
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
restart_primary:
    int processed = 0;
    TaskLink* node = scheduler->primary.link.next;
    while (node) {
        TaskLink* next = node->next;
        SchedulerTaskRaw* task = raw_task(node);
        if (task->on_tick) {
            if (task->flags & 2) {
repeat_primary:
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case 0:
                    FuncCtrl_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case 1:
                    break;
                case 2:
                    if (task->flags & 2) goto repeat_primary;
                    break;
                case 4:
                    processed = 0;
                    goto done_primary;
                case 3:
                    processed = 1;
                    goto done_primary;
                case 5:
                    processed = -1;
                    goto done_primary;
                case 6:
                    goto restart_primary;
                case 7:
                    if (task->on_remove) task->on_remove(task->context);
                    break;
                }
            }
            ++processed;
        }
        node = next;
    }
done_primary:
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return processed;
}

// 0x00449D40..0x00449E4B: FuncCtrl_RunSecondary and compiler-local switch table
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RunSecondary_00449d40(
        FuncCtrl* scheduler) {
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    int processed = 0;
    TaskLink* node = scheduler->secondary.link.next;
    while (node) {
        TaskLink* next = node->next;
        SchedulerTaskRaw* task = raw_task(node);
        if (task->on_tick) {
repeat_secondary:
            if (task->flags & 2) {
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case 0:
                    FuncCtrl_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case 1:
                    break;
                case 2:
                    if (task->flags & 2) goto repeat_secondary;
                    break;
                case 4:
                    processed = 0;
                    goto done_secondary;
                case 3:
                    processed = 1;
                    goto done_secondary;
                case 5:
                    processed = -1;
                    goto done_secondary;
                }
            }
            ++processed;
        }
        node = next;
    }
done_secondary:
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return processed;
}

// 0x00449ED0..0x00449F19: ?SchedulerCallback_Create@@
// The retail allocator is the project's recovered global operator new.
void* __cdecl operator new(unsigned int size);

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

extern "C" int* __stdcall SchedulerTask_Create(int callback) {
    CallbackTask* task = new CallbackTask;
    task->on_register = 0;
    task->on_remove = 0;
    // Read the initialized flags before publishing the callback and owned bit.
    unsigned int final_flags = *(volatile unsigned int*)&task->flags | 1u;
    task->on_tick = (TaskRoutine)callback;
    task->flags = final_flags;
    return reinterpret_cast<int*>(task);
}

// 0x0044A000: recovered in src/core/zunlib/scheduler_create_and_register.cpp.

// 0x0044A030: recovered in src/core/zunlib/scheduler_create_and_register_secondary.cpp.
