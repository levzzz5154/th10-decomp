// 0x00444FA0: draw solid primitives and restore the normal texture stages.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06edfan")
int SprtCtrlBatchView::DrawSolidFan(const RenderEntity* entity, const void* vertices, unsigned int count) {
    if (quad_count) Flush();
    if (cached_format != 4) {
        data_00491c30->Format(0x44);
        cached_format = 4;
    }
    SyncRenderState(entity);
    data_00491c30->Stage(0, 4, 2);
    data_00491c30->Stage(0, 1, 2);
    data_00491c30->Stage(0, 5, 0);
    data_00491c30->Stage(0, 2, 0);
    g_sprt_ctrl->Flush();
    data_00491c30->State(14, 0);
    data_00491c30->Draw(6, count - 2, vertices, 20);
    g_sprt_ctrl->cached_format = 0xFF;
    g_sprt_ctrl->cached_unknown_69 = 0xFF;
    g_sprt_ctrl->cached_blend = 3;
    g_sprt_ctrl->cached_unknown_6b = 0xFF;
    data_00491c30->Stage(0, 4, 4);
    data_00491c30->Stage(0, 1, 4);
    data_00491c30->Stage(0, 5, 2);
    data_00491c30->Stage(0, 2, 2);
    return 0;
}
#pragma code_seg()
