// Complete 96-byte factory at0x0042CD50: construct state and start its worker.
#include "th10/game/title.hpp"
#include "th10/platform/worker.hpp"
void* __cdecl operator new(unsigned int);
extern "C" unsigned int __stdcall Title_LoadWorkerEntry(void*);
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
    void*, unsigned int, PlatformWorkerEntry, void*, unsigned int, unsigned int*);
#pragma code_seg(".text$03cprogressfactory")
extern "C" __declspec(noinline) Title* __cdecl
Title_Create() {
    Title* state = new Title;
    PlatformWorker* worker = reinterpret_cast<PlatformWorker*>(&state->timer);
    worker->Stop();
    worker->entry = Title_LoadWorkerEntry;
    worker->running = 1;
    worker->stop_requested = 0;
    worker->thread = reinterpret_cast<void*>(asm_beginthreadex_00453683(
        0, 0, Title_LoadWorkerEntry, state, 0, &worker->thread_id));
    return state;
}
#pragma code_seg()
