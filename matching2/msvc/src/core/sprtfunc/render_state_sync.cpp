// 0x004425A0: synchronize cached blend and texture filtering before drawing.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$04bsync")
void SprtCtrlBatchView::SyncRenderState(const RenderEntity* entity) {
    if (cached_blend != ((entity->flags >> 4) & 3)) {
        Flush();
        cached_blend = (unsigned char)((entity->flags >> 4) & 3);
        switch (cached_blend) {
        case 0: g_d3d_device->State(20, 6); break;
        case 1: g_d3d_device->State(20, 2); break;
        }
    }
    if (cached_filter != (unsigned char)(entity->flags >> 31)) {
        Flush();
        cached_filter = (unsigned char)((entity->flags >> 31) & 1);
        if (cached_filter == 0) {
            g_d3d_device->Sampler(0, 5, 2);
            g_d3d_device->Sampler(0, 6, 2);
        } else {
            g_d3d_device->Sampler(0, 5, 1);
            g_d3d_device->Sampler(0, 6, 1);
        }
    }
    ++state_changes;
}
#pragma code_seg()
