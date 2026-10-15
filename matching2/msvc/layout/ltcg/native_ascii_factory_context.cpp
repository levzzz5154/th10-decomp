#include "th10/core/screen.hpp"
extern "C" float data_00476f78;
#include "runtime_selector_0043c970_scheduler_create.cpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"

#pragma code_seg(".text$10primary")
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RegisterPrimary(
        FuncCtrl* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->primary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}

#pragma code_seg(".text$30secondary")
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RegisterSecondary(
        FuncCtrl* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->secondary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}
#pragma code_seg()



#include "../../src/core/screen/configure.cpp"
#include "th10/math/timer.hpp"
#include "native_stage_update_context.cpp"
