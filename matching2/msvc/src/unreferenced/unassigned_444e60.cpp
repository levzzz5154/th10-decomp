// 0x00444E60: draw solid primitives and restore the normal texture stages.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06ebstrip")
int SprtCtrlBatchView::DrawSolidStrip(const RenderEntity* entity, const void* vertices, unsigned int count) {
    if (quad_count) Flush();
    if (cached_format != 4) {
        g_d3d_device->Format(0x44);
        cached_format = 4;
    }
    SyncRenderState(entity);
    g_d3d_device->Stage(0, 4, 2);
    g_d3d_device->Stage(0, 1, 2);
    g_d3d_device->Stage(0, 5, 0);
    g_d3d_device->Stage(0, 2, 0);
    g_sprt_ctrl->Flush();
    g_d3d_device->State(14, 0);
    g_d3d_device->Draw(5, count - 2, vertices, 20);
    g_sprt_ctrl->cached_format = 0xFF;
    g_sprt_ctrl->cached_unknown_69 = 0xFF;
    g_sprt_ctrl->cached_blend = 3;
    g_sprt_ctrl->cached_unknown_6b = 0xFF;
    g_d3d_device->Stage(0, 4, 4);
    g_d3d_device->Stage(0, 1, 4);
    g_d3d_device->Stage(0, 5, 2);
    g_d3d_device->Stage(0, 2, 2);
    return 0;
}
#pragma code_seg()
