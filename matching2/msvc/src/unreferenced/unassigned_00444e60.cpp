// 0x00444E60: draw solid primitives and restore the normal texture stages.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06ebstrip")
int AnimationManager_00442F50::DrawSolidStrip(const RenderEntity* entity, const void* vertices, unsigned int count) {
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
    data_00491c10->Flush();
    data_00491c30->State(14, 0);
    data_00491c30->Draw(5, count - 2, vertices, 20);
    data_00491c10->cached_format = 0xFF;
    data_00491c10->cached_unknown_69 = 0xFF;
    data_00491c10->cached_blend = 3;
    data_00491c10->cached_unknown_6b = 0xFF;
    data_00491c30->Stage(0, 4, 4);
    data_00491c30->Stage(0, 1, 4);
    data_00491c30->Stage(0, 5, 2);
    data_00491c30->Stage(0, 2, 2);
    return 0;
}
#pragma code_seg()
