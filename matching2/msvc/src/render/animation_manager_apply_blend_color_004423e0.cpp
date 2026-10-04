// 0x004423E0: apply blend, modulated texture-factor color, and filtering.
#include "th10/render/quad_batch.hpp"
inline unsigned int ScaleColor(unsigned char channel, unsigned char tint) {
    unsigned int result = (channel * (unsigned int)tint) >> 7;
    if (result >= 256) result = 255;
    return result;
}
union PackedColor { unsigned int packed; unsigned char channels[4]; };
#pragma code_seg(".text$04bablend")
extern "C" __declspec(noinline) void SyncRenderState_004423e0(
        AnimationManager_00442F50* manager, RenderEntity* entity) {
    if (manager->cached_blend != ((entity->flags >> 4) & 3)) {
        manager->Flush();
        manager->cached_blend = (unsigned char)((entity->flags >> 4) & 3);
        switch (manager->cached_blend) {
        case 0: data_00491c30->State(20, 6); break;
        case 1: data_00491c30->State(20, 2); break;
        case 2: data_00491c30->State(20, 2); break;
        }
    }
    PackedColor color;
    color.packed = (entity->flags & 0x8000) ? entity->color_secondary : entity->color;
    if (manager->fade_enabled) {
        const unsigned char* fade = &manager->fade_blue;
        unsigned char* channels = color.channels;
        channels[2] = (unsigned char)ScaleColor(color.channels[2], fade[2]);
        channels[1] = (unsigned char)ScaleColor(color.channels[1], fade[1]);
        channels[0] = (unsigned char)ScaleColor(color.channels[0], fade[0]);
        channels[3] = (unsigned char)ScaleColor(color.channels[3], fade[3]);
    }
    if (manager->cached_color != color.packed) {
        manager->Flush();
        manager->cached_color = color.packed;
        data_00491c30->State(60, color.packed);
    }
    if (manager->cached_filter != (unsigned char)(entity->flags >> 31)) {
        manager->Flush();
        manager->cached_filter = (unsigned char)((entity->flags >> 31) & 1);
        if (manager->cached_filter == 0) {
            data_00491c30->Sampler(0, 5, 2);
            data_00491c30->Sampler(0, 6, 2);
        } else {
            data_00491c30->Sampler(0, 5, 1);
            data_00491c30->Sampler(0, 6, 1);
        }
    }
    ++manager->state_changes;
}
#pragma code_seg()
