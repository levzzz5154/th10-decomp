// Compiler context only; never selected as recovered game code. The
// constructor, initializer and destructor are stand-ins shaped so each takes
// its receiver where the real one does.
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$07remove"
#include "../manager_teardown_native_0041adf0/scheduler.cpp"
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/card/card_create.cpp"

extern "C" void* g_func_ctrl;
extern "C" SchedulerTask* __stdcall ManagerCreateStandIn_Task(void* routine);

// C++ linkage: a call the compiler must assume can throw.
void __stdcall ManagerCreateStandIn_MayThrow(void* manager);

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

struct ManagerCreateStandInTasks {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
};
// With every callee-saved register busy the receiver stays on the stack.
static __forceinline void ManagerCreateStandIn_Unregister(ManagerCreateStandInTasks* manager) {
    SchedulerTask* task = manager->update_task;
    FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = manager->draw_task;
    scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// A call that may throw gives the factory its cleanup state; the two inlined
// removals keep every callee-saved register busy, so the receiver stays on
// the stack.
#pragma code_seg(".text$01ctor")
Card_00408c90::Card_00408c90() {
    ManagerCreateStandIn_Unregister(reinterpret_cast<ManagerCreateStandInTasks*>(this));
    ManagerCreateStandIn_MayThrow(0);
}

// The task in ESI and its priority in EDI leave EBX to the receiver.
#pragma code_seg(".text$02init")
int Card_00408c90::Initialize() {
    ManagerCreateStandInTasks* tasks = reinterpret_cast<ManagerCreateStandInTasks*>(this);
    SchedulerTask* update = ManagerCreateStandIn_Task(tail);
    update->reserved_flags &= ~1u;
    update->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), update, 0x18);
    tasks->update_task = update;
    SchedulerTask* draw = ManagerCreateStandIn_Task(tail + 4);
    draw->reserved_flags &= ~1u;
    draw->context = this;
    FuncCtrl_RegisterPrimary(static_cast<FuncCtrl*>(g_func_ctrl), draw, 0x2B);
    tasks->draw_task = draw;
    return *reinterpret_cast<int*>(tail);
}

#pragma code_seg(".text$03dtor")
Card_00408c90::~Card_00408c90() {
    ManagerCreateStandIn_Unregister(reinterpret_cast<ManagerCreateStandInTasks*>(this));
}

#pragma code_seg(".text$05context")
int __stdcall CardCreateCompilerContext() {
    return Card_Create_00408c90() != 0;
}
#pragma code_seg()
