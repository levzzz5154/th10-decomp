#include "th10/platform/worker.hpp"

// 0x0044C1C0 (56 bytes): start the worker thread.
//
// retail:
//   push esi / mov esi,eax / call PlatformWorker::Stop
//   mov ecx,[esp+8] / lea eax,[esi+8] / push eax / push 0 / push ecx / push edi
//   push 0 / push 0
//   mov [esi+18h],edi / mov [esi+10h],1 / mov [esi+0Ch],0
//   call _beginthreadex / add esp,18h / mov [esi+4],eax / pop esi / ret 4
//
// The worker handle comes from _beginthreadex, which runs `start` with `context`
// on the new thread and reports the thread id through thread_id.  The receiver
// arrives in EAX and the entry point in EDI: the internal ABI the retail /LTCG
// link chose for this worker family.  The cluster rebuilds that link so the
// whole-program pass selects the same registers.

// __beginthreadex, the CRT entry at 0x00453683.
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, PlatformWorkerEntry start,
        void* arglist, unsigned int initflag, unsigned int* thread_id);

#pragma code_seg(".text$0044c1c0_fn")
void PlatformWorker::Start(void* context, PlatformWorkerEntry start) {
    Stop();
    entry = start;
    running = 1;
    stop_requested = 0;
    thread = (void*)asm_beginthreadex_00453683(0, 0, start, context, 0, &thread_id);
}
#pragma code_seg()
