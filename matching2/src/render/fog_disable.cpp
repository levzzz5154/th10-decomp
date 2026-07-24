#include "th10/render/fog_disable.hpp"

// 0x00420CD0 - Disable fog when the cached fog word is set. Retail
// keeps the flag at manager+0x750 and the device pointer at +0x08: when
// the flag is live it flushes the staged geometry (0x00442F50), clears
// the flag, and issues SetRenderState(0x1C /* D3DRS_FOGENABLE */, 0)
// through the device vtable (+0xE4), returning that HRESULT; otherwise
// it returns 0 without touching the device. The flush and the device
// call are injected.
uint32_t Render_DisableFog(FogControl* state, void (*flush)(),
                           uint32_t (*set_render_state)(uint32_t state_id,
                                                        uint32_t value)) {
    if (state->fog_enabled == 0) {
        return 0;
    }
    if (flush != 0) {
        flush();
    }
    state->fog_enabled = 0;
    return set_render_state != 0 ? set_render_state(0x1C, 0) : 0;
}
