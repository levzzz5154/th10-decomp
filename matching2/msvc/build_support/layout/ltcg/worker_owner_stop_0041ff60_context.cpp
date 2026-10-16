// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ff60.cpp"
#include "../../../src/core/zunlib/platform_stop_worker_no_delete.cpp"
#include "../../../src/core/zunlib/platform_stop_worker.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(WorkerOwner** p, int n) {
    for (int i = 0; i < n; ++i) p[i]->StopWorker();
}
#pragma code_seg()
