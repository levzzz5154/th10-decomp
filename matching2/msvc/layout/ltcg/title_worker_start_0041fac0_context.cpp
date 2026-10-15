// Compiler-only ABI anchors and array caller. Only StartWorker is exported.
#include "../../src/game/loading/loading_start_worker.cpp"

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

#pragma code_seg(".text$12secondary")
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


#include "th10/platform/worker.hpp"

// ESI is selected by native LTCG from the real caller/callee relationship.
#pragma code_seg(".text$20stop")
__declspec(noinline) void PlatformWorker::Stop() {
    if (thread) {
        stop_requested = 1;
        running = 0;
        while (WaitForSingleObject(thread, 200) == 258) {
            stop_requested = 1;
            running = 0;
            Sleep(1);
        }
        CloseHandle(thread);
        thread = 0;
        entry = 0;
    }
}
#pragma code_seg()

struct Loading;
extern "C" Loading* __cdecl Loading_Create();

#pragma code_seg(".text$30context")
extern "C" int __cdecl LoadingStartCompilerContext(LoadingView** owners, int count) {
    while (count--) {
        (*owners++)->StartWorker();
    }
    return Loading_Create() != 0;
}
#pragma code_seg()
