// 0x00442670: finish the shared sprite quad and stage it for the batch.
//
// The caller has already written the four corners of one sprite into
// g_quad_vertices; this pipeline adds the manager's screen origin, optionally
// snaps the shared edges to the pixel grid, maps the sprite's texture
// coordinates onto them, culls the result against the active viewport and
// finally hands the quad to the state synchronizer and the batch appender.
#include "th10/render/quad_batch.hpp"

#pragma code_seg(".text$04c2quad")
int SprtCtrlBatchView::SubmitSpriteQuad(const RenderEntity* entity, unsigned int mode) {
    for (int corner = 0; corner < 4; ++corner) {
        g_quad_vertices[corner].x += origin_x;
        g_quad_vertices[corner].y += origin_y;
    }
    if (mode & 1) {
        // Retail's pixel snap is hand-written x87: round the left, right, top
        // and bottom edges to whole pixels and pull each back by a half pixel.
        // No C++98 spelling on this toolkit emits a bare `frndint`, so the
        // block is the original source's own assembly, assembled unmodified.
        __asm {
            fld  dword ptr [g_quad_vertices + 0x00]
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x1C]
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x04]
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x3C]
            frndint
            fsub dword ptr [data_00470ec]
            fst  dword ptr [g_quad_vertices + 0x3C]
            fstp dword ptr [g_quad_vertices + 0x58]
            fst  dword ptr [g_quad_vertices + 0x04]
            fstp dword ptr [g_quad_vertices + 0x20]
            fst  dword ptr [g_quad_vertices + 0x1C]
            fstp dword ptr [g_quad_vertices + 0x54]
            fst  dword ptr [g_quad_vertices + 0x00]
            fstp dword ptr [g_quad_vertices + 0x38]
        }
    }
    g_quad_vertices[0].u = g_quad_vertices[2].u = entity->texture->u0 + entity->uv_scroll_x;
    g_quad_vertices[1].u = g_quad_vertices[3].u = entity->texture->u1 + entity->uv_scroll_x;
    g_quad_vertices[0].v = g_quad_vertices[1].v = entity->texture->v0 + entity->uv_scroll_y;
    g_quad_vertices[2].v = g_quad_vertices[3].v = entity->texture->v1 + entity->uv_scroll_y;

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

    RenderTargetViewport* target = data_00491fac;
    if (max_x < (float)target->x) return 0;
    if ((float)target->y > max_y) return 0;
    if ((float)(target->x + target->width) < min_x) return 0;
    if ((float)(target->y + target->height) < min_y) return 0;

    if (cached_texture != entity->texture->texture) {
        cached_texture = entity->texture->texture;
        Flush();
        g_d3d_device->Texture(0, cached_texture);
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
        g_quad_vertices[0].color = color;
        g_quad_vertices[1].color = color;
        g_quad_vertices[2].color = color;
        g_quad_vertices[3].color = color;
    }
    SyncRenderState(entity);
    AppendQuad(g_quad_vertices);
    return 0;
}
#pragma code_seg()
