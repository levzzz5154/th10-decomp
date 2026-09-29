#include "th10/game/ui_thread_host.hpp"

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(void* critical_section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void* critical_section);
unsigned int __cdecl asm_beginthreadex_00453683(
    void* security, unsigned int stack_size, PlatformWorkerEntry start,
    void* context, unsigned int initflag, unsigned int* thread_id);
}

// 0x00420EA0 (118 bytes): replace the UI worker under its critical section.
#pragma code_seg(".text$02spawn")
int GameUiThreadHost::Spawn(PlatformWorkerEntry start, void* context) {
    EnterCriticalSection(critical_section);
    ++spawning;
    PlatformWorker* active_worker = &worker;
    active_worker->Stop();
    active_worker->entry = start;
    active_worker->running = 1;
    active_worker->stop_requested = 0;
    active_worker->thread = (void*)asm_beginthreadex_00453683(
        0, 0, start, context, 0, &active_worker->thread_id);
    LeaveCriticalSection(critical_section);
    --spawning;
    return 0;
}
#pragma code_seg()
