// 0x00420470: reset the frame-pacing state, then register the application's
// four main scheduler tasks on the object at 0x00491C28. The first task also
// runs an on-register hook; if that hook fails its result is returned and no
// further task is registered.
#include "th10/game/scheduler.hpp"

struct App_00491c28;

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall AppUpdate_0041ff80(void* app);
int __fastcall AppDraw_00420000(void* app);
int __fastcall AppPresent_004200c0(void* app);
int __fastcall AppFlush_004200d0(void* app);
int __fastcall AppOnRegister_004201b0(void* app);
extern Scheduler* data_00491be4;
extern App_00491c28 data_00491c28;
extern int data_00491fb4;
extern int data_00491fb8;
extern int data_00491fc0;
}

#pragma code_seg(".text$00fn")
extern "C" __declspec(noinline) int __stdcall App_RegisterTasks_00420470() {
    data_00491fb4 = -2;
    data_00491fb8 = 0;
    data_00491fc0 = 0;

    SchedulerTask* task = SchedulerCallback_Create_00449ed0(AppUpdate_0041ff80);
    task->context = &data_00491c28;
    task->reserved_flags |= 1;
    task->on_register = AppOnRegister_004201b0;
    int result = Scheduler_RegisterPrimary(data_00491be4, task, 1);
    if (result)
        return result;

    task = SchedulerCallback_Create_00449ed0(AppDraw_00420000);
    task->context = &data_00491c28;
    task->reserved_flags |= 1;
    Scheduler_RegisterSecondary(data_00491be4, task, 1);

    task = SchedulerCallback_Create_00449ed0(AppPresent_004200c0);
    task->context = &data_00491c28;
    task->reserved_flags |= 1;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x28);

    task = SchedulerCallback_Create_00449ed0(AppFlush_004200d0);
    task->context = &data_00491c28;
    task->reserved_flags |= 1;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x32);
    return 0;
}
#pragma code_seg()
