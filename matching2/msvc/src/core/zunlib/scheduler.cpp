// 0x00449C00..0x00449ED0: FuncCtrl_RunPrimary, FuncCtrl_RunSecondary2, SchedulerTask_Create
#include "th10/runtime/asm_symbols.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"

enum FuncCtrlTaskFlag {
    TASK_FLAG_OWNED = 1u,
    TASK_FLAG_ACTIVE = 2u
};

enum FuncCtrlTaskResult {
    TASK_REMOVE = 0,
    TASK_CONTINUE = 1,
    TASK_REPEAT = 2,
    TASK_STOP_OK = 3,
    TASK_STOP_ZERO = 4,
    TASK_STOP_ERROR = 5,
    TASK_RESTART_LIST = 6,
    TASK_RUN_ON_REMOVE = 7
};

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
            if (task->flags & TASK_FLAG_ACTIVE) {
repeat_primary:
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case TASK_REMOVE:
                    FuncCtrl_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case TASK_CONTINUE:
                    break;
                case TASK_REPEAT:
                    if (task->flags & TASK_FLAG_ACTIVE) goto repeat_primary;
                    break;
                case TASK_STOP_ZERO:
                    processed = 0;
                    goto done_primary;
                case TASK_STOP_OK:
                    processed = 1;
                    goto done_primary;
                case TASK_STOP_ERROR:
                    processed = -1;
                    goto done_primary;
                case TASK_RESTART_LIST:
                    goto restart_primary;
                case TASK_RUN_ON_REMOVE:
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
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RunSecondary2(
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
            if (task->flags & TASK_FLAG_ACTIVE) {
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case TASK_REMOVE:
                    FuncCtrl_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case TASK_CONTINUE:
                    break;
                case TASK_REPEAT:
                    if (task->flags & TASK_FLAG_ACTIVE) goto repeat_secondary;
                    break;
                case TASK_STOP_ZERO:
                    processed = 0;
                    goto done_secondary;
                case TASK_STOP_OK:
                    processed = 1;
                    goto done_secondary;
                case TASK_STOP_ERROR:
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
