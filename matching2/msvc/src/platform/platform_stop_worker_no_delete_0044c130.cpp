#include "th10/platform/worker.hpp"

// The native link keeps this public entry's ECX receiver and chooses ESI for
// the direct Stop call. Both complete functions belong to the same /LTCG link.
#pragma code_seg(".text$10caller")
__declspec(noinline) void PlatformWorker::StopNoDelete() {
    vtable = &platform_worker_vtable;
    Stop();
}
#pragma code_seg()
