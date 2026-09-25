// 0x00442AD0: finish the shared sprite quad with its texture u axis mirrored.
//
// The caller has already written the four corners of one sprite into
// data_004978c0; this pipeline adds the manager's screen origin, optionally
// snaps the shared edges to the pixel grid, maps the sprite's texture
// coordinates onto them, culls the result against the active viewport and
// finally hands the quad to the state synchronizer and the batch appender.
extern "C" double __cdecl asm_frnd_0045ebba(double value);
#include "th10/render/quad_batch.hpp"

#pragma code_seg(".text$04c4mirror")
int AnimationManager_00442F50::SubmitSpriteQuadMirrored(const RenderEntity* entity, unsigned int mode) {
    for (int corner = 0; corner < 4; ++corner) {
        data_004978c0[corner].x += origin_x;
        data_004978c0[corner].y += origin_y;
    }
    if (mode & 1) {
        // The CRT rounding helper follows the active x87 rounding mode.
        // Capture the four original edge coordinates before copying
        // each snapped value to its paired corner.
        const double snapped_left = asm_frnd_0045ebba(data_004978c0[0].x) - data_00470e8;
        const double snapped_right = asm_frnd_0045ebba(data_004978c0[1].x) - data_00470e8;
        const double snapped_top = asm_frnd_0045ebba(data_004978c0[0].y) - data_00470e8;
        const double snapped_bottom = asm_frnd_0045ebba(data_004978c0[2].y) - data_00470e8;

        data_004978c0[2].y = (float)snapped_bottom;
        data_004978c0[3].y = (float)snapped_bottom;
        data_004978c0[0].y = (float)snapped_top;
        data_004978c0[1].y = (float)snapped_top;
        data_004978c0[1].x = (float)snapped_right;
        data_004978c0[3].x = (float)snapped_right;
        data_004978c0[0].x = (float)snapped_left;
        data_004978c0[2].x = (float)snapped_left;
    }
    data_004978c0[0].u = data_004978c0[2].u = entity->texture->u1 + entity->uv_scroll_x;
    data_004978c0[1].u = data_004978c0[3].u = entity->texture->u0 + entity->uv_scroll_x;
    data_004978c0[0].v = data_004978c0[1].v = entity->texture->v0 + entity->uv_scroll_y;
    data_004978c0[2].v = data_004978c0[3].v = entity->texture->v1 + entity->uv_scroll_y;

    float max_x = data_004978c0[0].x > data_004978c0[1].x ? data_004978c0[0].x : data_004978c0[1].x;
    if (data_004978c0[2].x > max_x) max_x = data_004978c0[2].x;
    if (data_004978c0[3].x > max_x) max_x = data_004978c0[3].x;
    float max_y = data_004978c0[0].y > data_004978c0[1].y ? data_004978c0[0].y : data_004978c0[1].y;
    if (data_004978c0[2].y > max_y) max_y = data_004978c0[2].y;
    if (data_004978c0[3].y > max_y) max_y = data_004978c0[3].y;
    float min_x = data_004978c0[0].x < data_004978c0[1].x ? data_004978c0[0].x : data_004978c0[1].x;
    if (data_004978c0[2].x < min_x) min_x = data_004978c0[2].x;
    if (data_004978c0[3].x < min_x) min_x = data_004978c0[3].x;
    float min_y = data_004978c0[0].y < data_004978c0[1].y ? data_004978c0[0].y : data_004978c0[1].y;
    if (data_004978c0[2].y < min_y) min_y = data_004978c0[2].y;
    if (data_004978c0[3].y < min_y) min_y = data_004978c0[3].y;

    RenderTargetViewport* target = data_00491fac;
    if (max_x < (float)target->x) return 0;
    if ((float)target->y > max_y) return 0;
    if ((float)(target->x + target->width) < min_x) return 0;
    if ((float)(target->y + target->height) < min_y) return 0;

    if (cached_texture != entity->texture->texture) {
        cached_texture = entity->texture->texture;
        Flush();
        data_00491c30->Texture(0, cached_texture);
    }
    if (cached_format != 1) {
        Flush();
        cached_format = 1;
    }
    if (!(mode & 2)) {
        unsigned int color = (entity->flags & 0x8000) ? entity->color_secondary : entity->color;
        if (fade_enabled) {
            unsigned char* channels = (unsigned char*)&color;
            channels[2] = (unsigned char)AnimationColor_MultiplyChannel(channels[2], fade_red);
            channels[1] = (unsigned char)AnimationColor_MultiplyChannel(channels[1], fade_green);
            channels[0] = (unsigned char)AnimationColor_MultiplyChannel(channels[0], fade_blue);
            channels[3] = (unsigned char)AnimationColor_MultiplyChannel(channels[3], fade_alpha);
        }
        data_004978c0[0].color = color;
        data_004978c0[1].color = color;
        data_004978c0[2].color = color;
        data_004978c0[3].color = color;
    }
    SyncRenderState(entity);
    AppendQuad(data_004978c0);
    return 0;
}
#pragma code_seg()
