// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0041ff60_0041ff60.cpp"
#include "../../src/platform/platform_stop_worker_no_delete_0044c130.cpp"
#include "../../src/platform/platform_stop_worker_0044c150.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(WorkerOwner_0041ff60** p, int n) {
    for (int i = 0; i < n; ++i) p[i]->StopWorker();
}
#pragma code_seg()
