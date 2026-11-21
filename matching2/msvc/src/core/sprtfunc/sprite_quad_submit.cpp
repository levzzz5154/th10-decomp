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
        // MATCH: snap the four shared quad edges (TexturedVertex stride 0x1C:
        // [0].x=+0x00, [0].y=+0x04, [1].x=+0x1C, [1].y=+0x20, [2].x=+0x38,
        // [2].y=+0x3C, [3].x=+0x54, [3].y=+0x58) to integer pixels via x87
        // FRNDINT and subtract 0.5f (data_00470ec) for D3D9 texel alignment:
        //   v[0].x = v[2].x = round(v[0].x) - 0.5f;   (left)
        //   v[1].x = v[3].x = round(v[1].x) - 0.5f;   (right)
        //   v[0].y = v[1].y = round(v[0].y) - 0.5f;   (top)
        //   v[2].y = v[3].y = round(v[2].y) - 0.5f;   (bottom)
        // MSVC 7.1 has no C++ intrinsic that emits bare FRNDINT.
        __asm {
            fld  dword ptr [g_quad_vertices + 0x00] // left = v[0].x
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x1C] // right = v[1].x
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x04] // top = v[0].y
            frndint
            fsub dword ptr [data_00470ec]
            fld  dword ptr [g_quad_vertices + 0x3C] // bottom = v[2].y
            frndint
            fsub dword ptr [data_00470ec]
            fst  dword ptr [g_quad_vertices + 0x3C] // v[2].y = bottom
            fstp dword ptr [g_quad_vertices + 0x58] // v[3].y = bottom
            fst  dword ptr [g_quad_vertices + 0x04] // v[0].y = top
            fstp dword ptr [g_quad_vertices + 0x20] // v[1].y = top
            fst  dword ptr [g_quad_vertices + 0x1C] // v[1].x = right
            fstp dword ptr [g_quad_vertices + 0x54] // v[3].x = right
            fst  dword ptr [g_quad_vertices + 0x00] // v[0].x = left
            fstp dword ptr [g_quad_vertices + 0x38] // v[2].x = left
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
