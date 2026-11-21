// 0x00442670: finish the shared sprite quad and stage it for the batch.
//
// The caller has already written the four corners of one sprite into
// g_quad_vertices; this pipeline adds the manager's screen origin, optionally
// snaps the shared edges to the pixel grid, maps the sprite's texture
// coordinates onto them, culls the result against the active viewport and
// finally hands the quad to the state synchronizer and the batch appender.
#include "th10/render/sprite_quad.hpp"

#pragma code_seg(".text$04c2quad")
int SprtCtrlBatchView::SubmitSpriteQuad(const RenderEntity* entity, unsigned int mode) {
    ApplySpriteQuadOrigin(*this);
    if (mode & 1) {
        // Follow the active x87 rounding mode, then subtract half a pixel.
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

    StageSpriteQuad(*this, entity, mode);
    return 0;
}
#pragma code_seg()
