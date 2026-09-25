#include "th10/platform/worker.hpp"

// The retail tail-jump passes the render-state base in EAX to a private
// helper. That helper selects the PlatformWorker subobject at +0x62C,
// installs its base vtable, and stops it.
extern "C" void __cdecl asm_FUN_004659f0_004659f0() {
    PlatformWorker& worker = *reinterpret_cast<PlatformWorker*>(0x00492254UL);
    worker.vtable = reinterpret_cast<const void*>(0x004703E4UL);
    worker.Stop();
}
