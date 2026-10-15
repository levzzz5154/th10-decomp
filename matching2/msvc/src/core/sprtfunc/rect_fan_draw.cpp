// 0x004450E0: draw a textured triangle fan with depth writes disabled.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06ffan")
int SprtCtrlBatchView::DrawFan(const RenderEntity* entity, const void* vertices, unsigned int count) {
    if (quad_count) Flush();
    if (cached_format != 3) {
        g_d3d_device->Format(0x144);
        cached_format = 3;
    }
    SyncRenderState(entity);
    if (cached_texture != entity->texture->texture) {
        void* texture = entity->texture->texture;
        cached_texture = texture;
        RenderDevice* const volatile& current_device = g_d3d_device;
        RenderDevice* device = current_device;
        typedef long (__stdcall *SetTexture)(void*, unsigned int, void*);
        ((SetTexture)device->vtable[0x104 / 4])(device, 0, texture);
    }
    g_sprt_ctrl->Flush();
    g_d3d_device->State(14, 0);
    g_d3d_device->Stage(0, 6, 0);
    g_d3d_device->Stage(0, 3, 0);
    g_d3d_device->Draw(6, count - 2, vertices, 28);
    return 0;
}
#pragma code_seg()
