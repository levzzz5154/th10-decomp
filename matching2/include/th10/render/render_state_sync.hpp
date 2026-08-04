#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// Render-state cache fields inside the animation manager (retail
// offsets in comments).
struct RenderStateCache {
    uint8_t blend_mode;    // +0x3ADA68, cached blend selector
    int8_t filter_mode;    // +0x3ADA6E, cached filter selector
    int32_t sync_counter;  // +0x54, incremented every sync
};

// 0x004425A0 - Synchronize the device render state with an entity's
// flag word (retail entity+0x35C). Bits 4-5 select the blend mode: on
// change the staged geometry is flushed and blend 0 issues
// SetRenderState(0x14 /* D3DRS_DESTBLEND */, 6) while blend 1 issues
// SetRenderState(0x14, 2) (modes 2-3 only update the cache). The sign
// bit selects the filter mode: on change the flush runs and the
// magnification and minification sampler states (stage 0, ids 5 and 6)
// are both set to 1 (point) when the bit is set or 2 (linear) when
// clear. The sync counter always increments. Device calls and the flush
// are injected.
void AnmManager_SyncEntityRenderState(
    RenderStateCache* cache, uint32_t entity_flags, void (*flush)(),
    void (*set_render_state)(uint32_t state_id, uint32_t value),
    void (*set_sampler_state)(uint32_t stage, uint32_t state_id,
                              uint32_t value));
