#include "th10/platform/worker.hpp"

// 0x0044C200 (56 bytes): create the worker thread initially suspended.
// Shares Start's internal EAX receiver / EDI entry / stack context ABI.
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, PlatformWorkerEntry start,
        void* arglist, unsigned int initflag, unsigned int* thread_id);

#pragma code_seg(".text$46suspended")
void PlatformWorker::StartSuspended(void* context, PlatformWorkerEntry start) {
    Stop();
    entry = start;
    running = 1;
    stop_requested = 0;
    thread = (void*)asm_beginthreadex_00453683(0, 0, start, context, 4, &thread_id);
}
#pragma code_seg()
