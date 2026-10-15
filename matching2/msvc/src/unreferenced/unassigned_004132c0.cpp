// 0x004132C0: register an owner's draw task with the secondary scheduler
// list at priority 0x2F. Native LTCG passes the owner in EBX.
#include "th10/core/func_ctrl.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall TaskOwnerDraw(void* owner);
extern FuncCtrl* g_func_ctrl;
}

struct TaskOwner {
    unsigned char reserved_00[0x0C];
    SchedulerTask* draw_task;               // +0x0C

    __declspec(noinline) int InstallDrawTask();
};

#pragma code_seg(".text$00fn")
int TaskOwner::InstallDrawTask() {
    SchedulerTask* task = SchedulerTask_Create(TaskOwnerDraw);
    task->context = this;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x2F);
    draw_task = task;
    return 0;
}
#pragma code_seg()
