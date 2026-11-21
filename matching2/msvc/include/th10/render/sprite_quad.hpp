#pragma once
#include "th10/render/quad_batch.hpp"

static __forceinline void ApplySpriteQuadOrigin(const SprtCtrlBatchView& batch) {
    for (int corner = 0; corner < 4; ++corner) {
        g_quad_vertices[corner].x += batch.origin_x;
        g_quad_vertices[corner].y += batch.origin_y;
    }
}

// Reject only quads strictly outside the viewport: unordered edges must not be culled.
static __forceinline void StageSpriteQuad(SprtCtrlBatchView& batch, const RenderEntity* entity,
                                           unsigned int mode) {
    float max_x = g_quad_vertices[0].x > g_quad_vertices[1].x ? g_quad_vertices[0].x : g_quad_vertices[1].x;
    if (g_quad_vertices[2].x > max_x) max_x = g_quad_vertices[2].x;
    if (g_quad_vertices[3].x > max_x) max_x = g_quad_vertices[3].x;
    float max_y = g_quad_vertices[0].y > g_quad_vertices[1].y ? g_quad_vertices[0].y : g_quad_vertices[1].y;
    if (g_quad_vertices[2].y > max_y) max_y = g_quad_vertices[2].y;
    if (g_quad_vertices[3].y > max_y) max_y = g_quad_vertices[3].y;
    float min_x = g_quad_vertices[0].x < g_quad_vertices[1].x ? g_quad_vertices[0].x : g_quad_vertices[1].x;
    if (g_quad_vertices[2].x < min_x) min_x = g_quad_vertices[2].x;
    if (g_quad_vertices[3].x < min_x) min_x = g_quad_vertices[3].x;
    float min_y = g_quad_vertices[0].y < g_quad_vertices[1].y ? g_quad_vertices[0].y : g_quad_vertices[1].y;
    if (g_quad_vertices[2].y < min_y) min_y = g_quad_vertices[2].y;
    if (g_quad_vertices[3].y < min_y) min_y = g_quad_vertices[3].y;

    RenderTargetViewport* target = g_render_stage_active;
    if (max_x < (float)target->x) return;
    if ((float)target->y > max_y) return;
    if ((float)(target->x + target->width) < min_x) return;
    if ((float)(target->y + target->height) < min_y) return;

    if (batch.cached_texture != entity->texture->texture) {
        batch.cached_texture = entity->texture->texture;
        batch.Flush();
        g_d3d_device->Texture(0, batch.cached_texture);
    }
    if (batch.cached_format != 1) {
        batch.Flush();
        batch.cached_format = 1;
    }
    if (!(mode & 2)) {
        unsigned int color = (entity->flags & 0x8000) ? entity->color_secondary : entity->color;
        if (batch.fade_enabled) {
            unsigned char* channels = (unsigned char*)&color;
            channels[2] = (unsigned char)AnimationColor_MultiplyChannel(channels[2], batch.fade_red);
            channels[1] = (unsigned char)AnimationColor_MultiplyChannel(channels[1], batch.fade_green);
            channels[0] = (unsigned char)AnimationColor_MultiplyChannel(channels[0], batch.fade_blue);
            channels[3] = (unsigned char)AnimationColor_MultiplyChannel(channels[3], batch.fade_alpha);
        }
        g_quad_vertices[0].color = color;
        g_quad_vertices[1].color = color;
        g_quad_vertices[2].color = color;
        g_quad_vertices[3].color = color;
    }
    batch.SyncRenderState(entity);
    batch.AppendQuad(g_quad_vertices);
}
