// 0x00465A30: atexit destructor of the global worker at 0x00474DD4.
#include "th10/platform/worker.hpp"

extern "C" unsigned char data_00474dd4;

#pragma code_seg(".text$zzworker")
__declspec(noinline) void __cdecl StaticExit_Worker() {
    PlatformWorker* worker = reinterpret_cast<PlatformWorker*>(&data_00474dd4);
    worker->vtable = &platform_worker_vtable;
    worker->Stop();
}
#pragma code_seg()
