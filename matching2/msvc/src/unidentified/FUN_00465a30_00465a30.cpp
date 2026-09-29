#include "th10/platform/worker.hpp"

extern "C" unsigned char data_00474dd4;

#pragma code_seg(".text$zzworker")
__declspec(noinline) void __cdecl StopGlobalWorker_00465a30() {
    PlatformWorker* worker = reinterpret_cast<PlatformWorker*>(&data_00474dd4);
    worker->vtable = &platform_worker_vtable;
    worker->Stop();
}
#pragma code_seg()
