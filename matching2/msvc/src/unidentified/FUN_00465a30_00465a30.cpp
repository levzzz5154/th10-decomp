#include "th10/platform/worker.hpp"

// 0x00465A30 sets this global worker's base vtable before stopping it.
// The retail wrapper kept the worker receiver in ESI; the typed C++ call
// expresses that object relationship directly.
extern "C" void __cdecl asm_FUN_00465a30_00465a30() {
    PlatformWorker& worker =
        *reinterpret_cast<PlatformWorker*>(0x00474dd4UL);
    worker.vtable = reinterpret_cast<const void*>(0x004703e4UL);
    worker.Stop();
}
