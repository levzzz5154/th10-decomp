// Compiler context only; never selected as recovered game code. The manager's
// starter and destructor are stand-ins shaped so each takes its receiver
// where the real one does.
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/replay/replay_manager_create_00429610.cpp"

// C linkage: calls the compiler knows cannot throw, so the stand-in
// destructor needs no unwind state for the node array.
extern "C" void __stdcall ReplayManagerStandIn_Remove(void* scheduler, void* task);
extern "C" int __stdcall ReplayManagerStandIn_Load(const char* path);
extern "C" SchedulerTask* __stdcall ReplayManagerStandIn_Task(void* routine);

#pragma code_seg(".text$06primary")
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
#pragma code_seg()

static __forceinline void ReplayManagerStandIn_Unregister(void* task) {
    void* scheduler = g_func_ctrl;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ReplayManagerStandIn_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// With every callee-saved register busy the receiver stays on the stack.
#pragma code_seg(".text$03dtor")
ReplayManager_004296f0::~ReplayManager_004296f0() {
    void** tasks = reinterpret_cast<void**>(reserved_000);
    ReplayManagerStandIn_Unregister(tasks[2]);
    ReplayManagerStandIn_Unregister(tasks[3]);
}

// Both arguments are consumed before the first call, so they arrive in EAX
// and ECX; the task in ESI and its priority in EDI leave EBX to the receiver.
#pragma code_seg(".text$01start")
int ReplayManager_004296f0::Start(int start_mode, const char* replay_path) {
    mode = start_mode;
    *reinterpret_cast<const char**>(reserved_1c0) = replay_path;
    if (start_mode != 0)
        return -1;
    void** tasks = reinterpret_cast<void**>(reserved_000);
    SchedulerTask* update = ReplayManagerStandIn_Task(path);
    update->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), update, 0x10);
    tasks[2] = update;
    SchedulerTask* draw = ReplayManagerStandIn_Task(reserved_1c0);
    draw->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), draw, 0x11);
    tasks[3] = draw;
    return 0;
}

#pragma code_seg(".text$05context")
int __stdcall ReplayManagerStartCompilerContext(int start_mode, const char* replay_path) {
    return ReplayManager_Create_00429610(start_mode, replay_path) != 0;
}
#pragma code_seg()
