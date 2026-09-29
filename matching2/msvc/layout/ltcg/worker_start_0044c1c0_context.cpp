// Compiler context only; not recovered game code.  It mirrors the shape of the
// retail callers of the worker Start variants: each host holds the worker and stays live across
// the call and is passed as the thread context, while the worker's address is
// computed fresh for the call. A second array supplies UI-thread hosts for Spawn.
#include "../../src/platform/worker_start.cpp"
#include "th10/game/ui_thread_host.hpp"

struct WorkerHost {
    char pad0[0x10];
    PlatformWorker worker;              // +0x10, like the retail callers
    char pad1[0x1c];
    unsigned int state;                 // +0x48
};

#pragma code_seg(".text$50context")
extern "C" int __cdecl WorkerStartCompilerContext(WorkerHost** hosts, int count,
                                                  PlatformWorkerEntry* entries,
                                                  GameUiThreadHost** ui_hosts) {
    while (count--) {
        WorkerHost* host = *hosts++;
        host->worker.Start(host, *entries++);
        host->worker.StartSuspended(host, *entries++);
        GameUiThreadHost* ui = *ui_hosts++;
        ui->Spawn(*entries++, ui);
        host->state = 2;
    }
    return 0;
}
#pragma code_seg()
