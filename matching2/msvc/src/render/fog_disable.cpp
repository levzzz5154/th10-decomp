#include <stddef.h>

#include "th10/render/quad_batch.hpp"

// Existing assembly callers use the old C entry label.  Both live callers
// supply the same singleton state object in EDI; this fallback keeps that
// no-argument call target while the implementation names the state directly.
#pragma comment(linker, "/alternatename:_asm_FUN_00420cd0_00420cd0=_RenderStageState_DisableFog_00420CD0")

extern "C" unsigned char data_00491c28;

struct RenderStageFogState_00420CD0 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                 // +0x08
    unsigned char reserved_00C[0x750 - 0x0C];
    int fog_dirty;                        // +0x750
};

static_assert(offsetof(RenderStageFogState_00420CD0, fog_dirty) == 0x750,
              "retail fog flag offset changed");

// 0x00420CD0: flush pending animation quads, clear the pending fog flag, and
// disable D3D render state 28.  At the retail boundary EDI carries
// &data_00491c28; reading that singleton directly expresses the behavior in
// ordinary C++ without depending on a compiler-specific EDI calling
// convention.  The two callers and their EDI setup are documented in
// reference/recovery_notes/fog_disable_00420cd0.md.
extern "C" int __cdecl RenderStageState_DisableFog_00420CD0(void) {
    RenderStageFogState_00420CD0* const state =
            reinterpret_cast<RenderStageFogState_00420CD0*>(&data_00491c28);
    if (!state->fog_dirty)
        return 0;

    data_00491c10->Flush();
    RenderDevice* const device = state->device;
    state->fog_dirty = 0;
    return device->State(28, 0);
}
