#include "th10/game/scheduler.hpp"
#include "th10/platform/worker.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
extern Scheduler* data_00491be4;
int __fastcall TitleWorkerPrimary(void* owner);
int __fastcall TitleWorkerSecondary(void* owner);
unsigned int __stdcall TitleWorkerThreadMain(void* owner);
unsigned int __cdecl asm_beginthreadex_00453683(
    void* security, unsigned int stack_size, PlatformWorkerEntry start,
    void* context, unsigned int initflag, unsigned int* thread_id);
}

struct TitleWorkerOwner {
    unsigned char reserved_00[8];
    SchedulerTask* primary_task;             // +0x08
    SchedulerTask* secondary_task;           // +0x0c
    PlatformWorker worker;                  // +0x10

    __declspec(noinline) int StartWorker();
};

typedef char TitleWorkerOwner_primary_offset[
    offsetof(TitleWorkerOwner, primary_task) == 8 ? 1 : -1];
typedef char TitleWorkerOwner_secondary_offset[
    offsetof(TitleWorkerOwner, secondary_task) == 12 ? 1 : -1];
typedef char TitleWorkerOwner_worker_offset[
    offsetof(TitleWorkerOwner, worker) == 16 ? 1 : -1];

// 0x0041FAC0 (140 bytes): register two tasks and start their owner's worker.
#pragma code_seg(".text$02starter")
int TitleWorkerOwner::StartWorker() {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0(TitleWorkerPrimary);
    // Clear callback flag 0x2 before registration.
    *(unsigned int*)((unsigned char*)primary + 4) &= ~2u;
    primary->context = this;
    Scheduler_RegisterPrimary(data_00491be4, primary, 3);
    primary_task = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0(TitleWorkerSecondary);
    *(unsigned int*)((unsigned char*)secondary + 4) &= ~2u;
    secondary->context = this;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 2);
    secondary_task = secondary;

    PlatformWorker* active_worker = &worker;
    active_worker->Stop();
    active_worker->entry = TitleWorkerThreadMain;
    active_worker->running = 1;
    active_worker->stop_requested = 0;
    active_worker->thread = (void*)asm_beginthreadex_00453683(
        0, 0, TitleWorkerThreadMain, this, 0, &active_worker->thread_id);
    return 0;
}
#pragma code_seg()
