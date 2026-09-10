#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

void __cdecl operator delete(void*);

#pragma code_seg(".text$10primary")
extern "C" __declspec(noinline) int __stdcall Scheduler_RegisterPrimary(
        Scheduler* scheduler, SchedulerTask* task, int priority) {
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
extern "C" __declspec(noinline) int __stdcall Scheduler_RegisterSecondary(
        Scheduler* scheduler, SchedulerTask* task, int priority) {
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
#pragma code_seg(".text$50locked")
extern "C" __declspec(noinline) void __stdcall Scheduler_RemoveLocked(
        Scheduler* scheduler, SchedulerTask* task) {
    if (!task)
        return;
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    Scheduler_Remove(task, scheduler);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
}
#pragma code_seg(".text$70remove")
extern "C" __declspec(noinline) void __fastcall Scheduler_Remove(SchedulerTask* task, Scheduler* scheduler) {
    if (!task) return;
    TaskLink* node = &scheduler->primary.link;
    while (node) {
        if (node->task == task) break;
        node = node->next;
    }
    if (!node) {
        node = &scheduler->secondary.link;
        while (node) {
            if (node->task == task) break;
            node = node->next;
        }
    }
    if (node && node->previous) {
        node->Unlink();
        task->on_tick = 0;
        if (task->heap_owned) delete task;
    }
}
#pragma code_seg()
