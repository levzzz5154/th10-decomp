// 0x0041FF60: stop the worker embedded at +0x62C of its owner.
#include "th10/platform/worker.hpp"

struct WorkerOwner_0041ff60 {
    unsigned char unknown_000[0x62C];
    PlatformWorker worker;

    void StopWorker();
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void WorkerOwner_0041ff60::StopWorker() {
    worker.vtable = &platform_worker_vtable;
    worker.Stop();
}
#pragma code_seg()
