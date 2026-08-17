#include "th10/render/render_state_sync.hpp"


// 0x004425A0 - Synchronize the device render state with an entity's
// flag word. Retail keeps the manager in EAX and the entity in EDI and
// calls the device vtable directly (SetRenderState at +0xE4,
// SetSamplerState at +0x114); both are injected here together with the
// staged-geometry flush (0x00442F50).

void AnmManager_SyncEntityRenderState(
        RenderStateCache* cache, uint32_t entity_flags, void (*flush)(),
        void (*set_render_state)(uint32_t state_id, uint32_t value),
        void (*set_sampler_state)(uint32_t stage, uint32_t state_id,
                                  uint32_t value)) {
    const uint8_t blend = (uint8_t)((entity_flags >> 4) & 3u);
    if (cache->blend_mode != blend) {
        if (flush != 0) {
            flush();
        }
        cache->blend_mode = blend;
        if (blend == 0) {
            set_render_state(0x14, 6);
        } else if (blend == 1) {
            set_render_state(0x14, 2);
        }
    }

    const int8_t filter = (int8_t)((entity_flags & 0x80000000u) != 0 ? 1 : 0);
    if (cache->filter_mode != filter) {
        if (flush != 0) {
            flush();
        }
        cache->filter_mode = filter;
        const uint32_t value = filter == 0 ? 2u : 1u;
        set_sampler_state(0, 5, value);
        set_sampler_state(0, 6, value);
    }

    cache->sync_counter += 1;
}
