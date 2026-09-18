// Compiler context only; not recovered game code.  It mirrors the shape of the
// retail callers of Start: the host object holds the worker, stays live across
// the call and is passed as the thread context, while the worker's address is
// computed fresh for the call.
#include "../../src/platform/worker_start.cpp"

struct WorkerHost {
    char pad0[0x10];
    PlatformWorker worker;              // +0x10, like the retail callers
    char pad1[0x1c];
    unsigned int state;                 // +0x30
};

#pragma code_seg(".text$50context")
extern "C" int __cdecl WorkerStartCompilerContext(WorkerHost** hosts, int count,
                                                  PlatformWorkerEntry* entries) {
    while (count--) {
        WorkerHost* host = *hosts++;
        host->worker.Start(host, *entries++);
        host->state = 2;
    }
    return 0;
}
#pragma code_seg()
