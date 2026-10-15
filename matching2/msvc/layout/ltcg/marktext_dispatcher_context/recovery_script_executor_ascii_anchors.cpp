// Compiler-only full semantic anchors for the executor's ASCII factory call.
// Every helper retains its complete retail behavior; none is a selected region.
#include <string.h>
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_ascii_anchors.hpp"
#include "th10/game/marktext_dispatcher_context/thread_sync.hpp"

extern "C" {
extern FuncCtrl* g_func_ctrl;
extern const float RecoveryAsciiFrameSpeed_00476f78;
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall RecoveryAsciiBasicTick_0043bd40(void*);
int __fastcall RecoveryAsciiDraw0_0043c1a0(void*);
int __fastcall RecoveryAsciiTick1_0043c550(void*);
int __fastcall RecoveryAsciiTick2_0043c230(void*);
int __fastcall RecoveryAsciiDraw2_0043c2c0(void*);
int __fastcall RecoveryAsciiTick4_0043c460(void*);
int __fastcall RecoveryAsciiDraw4_0043c500(void*);
int __fastcall RecoveryAsciiTick6_0043c310(void*);
int __fastcall RecoveryAsciiDraw6_0043c3c0(void*);
int __fastcall RecoveryAsciiDraw7_0043c410(void*);
int __fastcall RecoveryAsciiTick8_0043c710(void*);
int __fastcall RecoveryAsciiRemove_0043c870(void*);
}

// The factories' scheduler chain is supplied in full to expose its private
// callback EAX / priority EDI / owner stack argument to native LTCG.
#pragma code_seg(".text$00449ae0_ascii_anchor")
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

#pragma code_seg(".text$00449b70_ascii_anchor")
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

#pragma code_seg(".text$0044a000_ascii_anchor")
extern "C" __declspec(noinline) SchedulerTask* __stdcall
RecoveryAsciiRegisterPrimary_0044a000(TaskRoutine callback, int priority,
                                    void* owner) {
    SchedulerTask* task = SchedulerCallback_Create_00449ed0(callback);
    task->context = owner;
    *(unsigned int*)((unsigned char*)task + 4) |= 2u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, priority);
    return task;
}

#pragma code_seg(".text$0044a030_ascii_anchor")
extern "C" __declspec(noinline) SchedulerTask* __stdcall
RecoveryAsciiRegisterSecondary_0044a030(TaskRoutine callback, int priority,
                                      void* owner) {
    SchedulerTask* task = SchedulerCallback_Create_00449ed0(callback);
    task->context = owner;
    *(unsigned int*)((unsigned char*)task + 4) |= 2u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, priority);
    return task;
}

#pragma code_seg(".text$0043c970_fn")
extern "C" void __stdcall RecoveryAscii_Register_0043c970(
    RecoveryAsciiManager_0043c8b0* manager, unsigned int draw_priority,
    unsigned int mode, unsigned int payload, unsigned int argument_20,
    unsigned int argument_24, unsigned int argument_28) {
    switch (mode) {
    case 0:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiBasicTick_0043bd40, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw0_0043c1a0, draw_priority, manager);
        break;
    case 1:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick1_0043c550, 14, manager);
        break;
    case 3:
        manager->color = 255;
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiBasicTick_0043bd40, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw2_0043c2c0, draw_priority, manager);
        break;
    case 2:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick2_0043c230, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw2_0043c2c0, draw_priority, manager);
        break;
    case 4:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick4_0043c460, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw4_0043c500, draw_priority, manager);
        break;
    case 5:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick2_0043c230, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw0_0043c1a0, draw_priority, manager);
        break;
    case 6:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick6_0043c310, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw6_0043c3c0, draw_priority, manager);
        break;
    case 7:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick6_0043c310, 14, manager);
        manager->draw_task = RecoveryAsciiRegisterSecondary_0044a030(
            RecoveryAsciiDraw7_0043c410, draw_priority, manager);
        break;
    case 8:
        manager->update_task = RecoveryAsciiRegisterPrimary_0044a000(
            RecoveryAsciiTick8_0043c710, 14, manager);
        break;
    }
    // Retail falls through even for an out-of-range mode and dereferences
    // the pre-existing update_task; there is deliberately no early return.
    manager->update_task->on_remove = RecoveryAsciiRemove_0043c870;
    if ((manager->timer.flags & 1u) == 0) {
        manager->timer.current = 0;
        manager->timer.previous = static_cast<int>(0xfff0bdc1u);
        manager->timer.elapsed = 0.0f;
        manager->timer.speed = &RecoveryAsciiFrameSpeed_00476f78;
        manager->timer.flags |= 1u;
    }
    manager->timer.current = 0;
    manager->timer.elapsed = 0.0f;
    manager->timer.previous = -1;
    manager->payload = payload;
    manager->mode = mode;
    manager->argument_20 = argument_20;
    manager->argument_24 = argument_24;
    manager->argument_28 = argument_28;
}

#pragma code_seg(".text$0043c8b0_fn")
extern "C" RecoveryAsciiManager_0043c8b0* __stdcall
RecoveryAscii_Create_0043c8b0(unsigned int draw_priority, unsigned int mode,
    unsigned int payload, unsigned int argument_20,
    unsigned int argument_24, unsigned int argument_28) {
    RecoveryAsciiManager_0043c8b0* manager = new RecoveryAsciiManager_0043c8b0;
    if (manager) {
        memset(manager, 0, sizeof(*manager));
        manager->flags |= 2u;
        RecoveryAscii_Register_0043c970(manager, draw_priority, mode,
            payload, argument_20, argument_24, argument_28);
    }
    return manager;
}
#pragma code_seg()
