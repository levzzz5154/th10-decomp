// Complete 96-byte factory at0x0042CD50: construct state and start its worker.
#include "th10/game/progress_worker_0042c920.hpp"
#include "th10/platform/worker.hpp"
void* __cdecl operator new(unsigned int);
extern "C" unsigned int __stdcall ProgressWorker_Thread_0042c9f0(void*);
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
    void*, unsigned int, PlatformWorkerEntry, void*, unsigned int, unsigned int*);
#pragma code_seg(".text$03cprogressfactory")
extern "C" __declspec(noinline) ProgressWorker_0042c920* __cdecl
asm_ProgressManager_CreateAndStartWorker_0042cd50() {
    ProgressWorker_0042c920* state = new ProgressWorker_0042c920;
    PlatformWorker* worker = reinterpret_cast<PlatformWorker*>(&state->timer);
    worker->Stop();
    worker->entry = ProgressWorker_Thread_0042c9f0;
    worker->running = 1;
    worker->stop_requested = 0;
    worker->thread = reinterpret_cast<void*>(asm_beginthreadex_00453683(
        0, 0, ProgressWorker_Thread_0042c9f0, state, 0, &worker->thread_id));
    return state;
}
#pragma code_seg()
