// Compiler context only; never selected as recovered game code. The manager's
// initializer and destructor are stand-ins shaped so each takes its receiver
// where the real one does.
#include "../../../../src/game/bullet/bullet_manager_create.cpp"

extern "C" SchedulerTask* __stdcall ManagerCreateStandIn_Task(void* routine);

// C linkage: a removal the compiler knows cannot throw, so the stand-in
// destructor needs no unwind state for the element array.
extern "C" void __stdcall ManagerCreateStandIn_Remove(FuncCtrl* scheduler, SchedulerTask* task);

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

static __forceinline void ManagerCreateStandIn_Unregister(SchedulerTask* task) {
    FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerCreateStandIn_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

extern "C" SchedulerTask* __stdcall ManagerCreateStandIn_Task(void* routine);

// The task in ESI and its priority in EDI leave EBX to the receiver.
#pragma code_seg(".text$02init")
int BulletManager2::Initialize() {
    SchedulerTask* update = ManagerCreateStandIn_Task(reserved_010);
    update->reserved_flags &= ~1u;
    update->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), update, 0x15);
    update_task = update;
    SchedulerTask* draw = ManagerCreateStandIn_Task(reserved_010 + 4);
    draw->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), draw, 0x19);
    draw_task = draw;
    return 0;
}

// With every callee-saved register busy the receiver stays on the stack.
#pragma code_seg(".text$03dtor")
BulletManager2::~BulletManager2() {
    ManagerCreateStandIn_Unregister(update_task);
    ManagerCreateStandIn_Unregister(draw_task);
}

#pragma code_seg(".text$05context")
int __stdcall BulletManagerCreateCompilerContext() {
    return BulletManager_Create2() != 0;
}
#pragma code_seg()
