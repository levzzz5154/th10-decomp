// 0x004132C0: register an owner's draw task with the secondary scheduler
// list at priority 0x2F. Native LTCG passes the owner in EBX.
#include "th10/core/func_ctrl.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall TaskOwnerDraw_00413690(void* owner);
extern FuncCtrl* g_func_ctrl;
}

struct TaskOwner_004132c0 {
    unsigned char reserved_00[0x0C];
    SchedulerTask* draw_task;               // +0x0C

    __declspec(noinline) int InstallDrawTask();
};

#pragma code_seg(".text$00fn")
int TaskOwner_004132c0::InstallDrawTask() {
    SchedulerTask* task = SchedulerCallback_Create_00449ed0(TaskOwnerDraw_00413690);
    task->context = this;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x2F);
    draw_task = task;
    return 0;
}
#pragma code_seg()
