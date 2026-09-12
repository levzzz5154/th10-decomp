#pragma once

#include <cstdint>

// Render-manager fragment for the fog toggle (retail offsets in
// comments).
struct FogControl {
    uint32_t fog_enabled;  // +0x750, cached D3DRS_FOGENABLE value
};

// 0x00420CD0 - Disable fog when the cached fog word is set: flush the
// staged geometry, clear the cache word, and issue
// SetRenderState(D3DRS_FOGENABLE, 0), returning its HRESULT (0 when the
// cache was already clear).
uint32_t Render_DisableFog(FogControl* state, void (*flush)(),
                           uint32_t (*set_render_state)(uint32_t state_id,
                                                        uint32_t value));
