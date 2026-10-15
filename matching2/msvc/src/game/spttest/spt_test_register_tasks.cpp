// 0x0042BBD0: install the script tester's (SptTest, spttest.cpp) update task on the primary scheduler
// list (priority 5) and its draw task on the secondary list (priority 0x27).
// Native LTCG passes the pool in EBX.
#include "th10/core/func_ctrl.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall SptTestUpdateTask_0042c580(void* pool);
int __fastcall SptTestDrawTask_0042c590(void* pool);
extern FuncCtrl* g_func_ctrl;
}

#include "th10/game/spt_test_tasks.hpp"

#pragma code_seg(".text$00fn")
int SptTestTaskView::InstallTasks() {
    SchedulerTask* task = SchedulerTask_Create(SptTestUpdateTask_0042c580);
    task->reserved_flags |= 1;
    task->context = this;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 5);
    update_task = task;

    task = SchedulerTask_Create(SptTestDrawTask_0042c590);
    task->reserved_flags |= 1;
    task->context = this;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x27);
    draw_task = task;
    return 0;
}
#pragma code_seg()
