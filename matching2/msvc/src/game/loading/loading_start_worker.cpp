#include "th10/core/func_ctrl.hpp"
#include "th10/platform/worker.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
extern FuncCtrl* g_func_ctrl;
int __fastcall LoadingPrimary(void* owner);
int __fastcall LoadingSecondary(void* owner);
unsigned int __stdcall LoadingThreadMain(void* owner);
unsigned int __cdecl asm_beginthreadex_00453683(
    void* security, unsigned int stack_size, PlatformWorkerEntry start,
    void* context, unsigned int initflag, unsigned int* thread_id);
}

#include "th10/game/loading_view.hpp"

// 0x0041FAC0 (140 bytes): register two tasks and start their owner's worker.
#pragma code_seg(".text$02starter")
int LoadingView::StartWorker() {
    SchedulerTask* primary = SchedulerTask_Create(LoadingPrimary);
    // Clear callback flag 0x2 before registration.
    *(unsigned int*)((unsigned char*)primary + 4) &= ~2u;
    primary->context = this;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 3);
    primary_task = primary;

    SchedulerTask* secondary = SchedulerTask_Create(LoadingSecondary);
    *(unsigned int*)((unsigned char*)secondary + 4) &= ~2u;
    secondary->context = this;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 2);
    secondary_task = secondary;

    PlatformWorker* active_worker = &worker;
    active_worker->Stop();
    active_worker->entry = LoadingThreadMain;
    active_worker->running = 1;
    active_worker->stop_requested = 0;
    active_worker->thread = (void*)asm_beginthreadex_00453683(
        0, 0, LoadingThreadMain, this, 0, &active_worker->thread_id);
    return 0;
}
#pragma code_seg()
