// 0x00444CE0: draw an entity's textured triangle strip.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06bstrip")
int AnimationManager_00442F50::DrawStrip(const RenderEntity* entity, const void* vertices, unsigned int count) {
    if (!(entity->flags & 1)) return -1;
    if (!(entity->flags & 2)) return -1;
    if (((const unsigned char*)&entity->color)[3] == 0) return -1;
    if (quad_count) Flush();
    if (cached_texture != entity->texture->texture) {
        void* texture = entity->texture->texture;
        cached_texture = texture;
        RenderDevice* const volatile& current_device = data_00491c30;
        RenderDevice* device = current_device;
        typedef long (__stdcall *SetTexture)(void*, unsigned int, void*);
        ((SetTexture)device->vtable[0x104 / 4])(device, 0, texture);
    }
    if (cached_format != 3) {
        data_00491c30->Format(0x144);
        cached_format = 3;
    }
    SyncRenderState(entity);
    data_00491c30->Stage(0, 6, 0);
    data_00491c30->Stage(0, 3, 0);
    data_00491c30->Draw(5, count - 2, vertices, 28);
    return 0;
}
#pragma code_seg()
