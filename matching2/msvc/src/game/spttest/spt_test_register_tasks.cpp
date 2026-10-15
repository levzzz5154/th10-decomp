// 0x0042BBD0: install the script tester's (SptTest, spttest.cpp) update task on the primary scheduler
// list (priority 5) and its draw task on the secondary list (priority 0x27).
// Native LTCG passes the pool in EBX.
#include "th10/game/scheduler.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall SptTestUpdateTask_0042c580(void* pool);
int __fastcall SptTestDrawTask_0042c590(void* pool);
extern Scheduler* data_00491be4;
}

#include "th10/game/spt_test_tasks.hpp"

#pragma code_seg(".text$00fn")
int SptTestTaskView::InstallTasks() {
    SchedulerTask* task = SchedulerCallback_Create_00449ed0(SptTestUpdateTask_0042c580);
    task->reserved_flags |= 1;
    task->context = this;
    Scheduler_RegisterPrimary(data_00491be4, task, 5);
    update_task = task;

    task = SchedulerCallback_Create_00449ed0(SptTestDrawTask_0042c590);
    task->reserved_flags |= 1;
    task->context = this;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x27);
    draw_task = task;
    return 0;
}
#pragma code_seg()
