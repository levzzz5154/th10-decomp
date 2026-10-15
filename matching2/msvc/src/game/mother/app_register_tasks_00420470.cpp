// 0x00420470: reset the frame-pacing state, then register the application's
// four main scheduler tasks on the object at 0x00491C28. The first task also
// runs an on-register hook; if that hook fails its result is returned and no
// further task is registered.
#include "th10/core/func_ctrl.hpp"

struct App_00491c28;

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall AppUpdate(void* app);
int __fastcall AppDraw(void* app);
int __fastcall AppPresent_004200c0(void* app);
int __fastcall AppFlush(void* app);
int __fastcall AppOnRegister(void* app);
extern FuncCtrl* g_func_ctrl;
extern App_00491c28 g_application;
extern int g_main_task_status_a;
extern int g_main_state;
extern int g_main_task_status_b;
}

#pragma code_seg(".text$00fn")
extern "C" __declspec(noinline) int __stdcall App_RegisterTasks() {
    g_main_task_status_a = -2;
    g_main_state = 0;
    g_main_task_status_b = 0;

    SchedulerTask* task = SchedulerTask_Create(AppUpdate);
    task->context = &g_application;
    task->reserved_flags |= 1;
    task->on_register = AppOnRegister;
    int result = FuncCtrl_RegisterPrimary(g_func_ctrl, task, 1);
    if (result)
        return result;

    task = SchedulerTask_Create(AppDraw);
    task->context = &g_application;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 1);

    task = SchedulerTask_Create(AppPresent_004200c0);
    task->context = &g_application;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x28);

    task = SchedulerTask_Create(AppFlush);
    task->context = &g_application;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x32);
    return 0;
}
#pragma code_seg()
