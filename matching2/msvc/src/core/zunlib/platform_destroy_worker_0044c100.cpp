#include "th10/platform/worker.hpp"

extern "C" void __cdecl crt_free_startup(void* memory);

#pragma code_seg(".text$05destroy")
__declspec(noinline) PlatformWorker* PlatformWorker::Destroy(
        unsigned int should_free) {
    vtable = &platform_worker_vtable;
    Stop();
    if (should_free & 1)
        crt_free_startup(this);
    return this;
}
#pragma code_seg()
