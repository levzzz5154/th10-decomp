// 0x00443080..0x00443282: build and submit one anchored sprite quad.
// Placement flags independently anchor x and y at the center, near edge, or
// far edge. Centered edges use the toolkit's float overload of CRT floor.
// All four z values use the entity's complete placement sum; submit mode 1.
//
// Native LTCG derives the retail entry: entity in ESI, manager on the stack,
// and RET 4. The dedicated driver contains the complete real draw dispatcher
// and genuine complete submission helpers; only this 515-byte body is selected.
#include "th10/render/quad_batch.hpp"
#include <math.h>

#pragma code_seg(".text$06b01z00quad")
extern "C" __declspec(noinline) int EntityDraw(RenderEntity* entity,
                                                       SprtCtrlBatchView* manager) {
    float width = entity->sprite_width * entity->scale_x;
    float height = entity->sprite_height * entity->scale_y;
    float half_height = height * 0.5f;
    float left, top;

    switch ((entity->flags >> 18) & 3) {
    case 0:
        left = (float)floor(entity->render_offset.x + entity->position.x
                            + entity->base_position.x - width * 0.5f);
        g_quad_vertices[0].x = g_quad_vertices[2].x = left;
        g_quad_vertices[1].x = g_quad_vertices[3].x = g_quad_vertices[2].x + width;
        break;
    case 1:
        left = entity->base_position.x + entity->position.x + entity->render_offset.x;
        g_quad_vertices[0].x = g_quad_vertices[2].x = left;
        g_quad_vertices[1].x = g_quad_vertices[3].x =
            entity->base_position.x + entity->position.x + width + entity->render_offset.x;
        break;
    case 2:
        g_quad_vertices[0].x = g_quad_vertices[2].x =
            entity->base_position.x + entity->position.x + entity->render_offset.x - width;
        g_quad_vertices[1].x = g_quad_vertices[3].x =
            entity->base_position.x + entity->position.x + entity->render_offset.x;
        break;
    }

    switch ((entity->flags >> 20) & 3) {
    case 0:
        top = (float)floor(entity->render_offset.y + entity->position.y
                           + entity->base_position.y - half_height);
        g_quad_vertices[0].y = g_quad_vertices[1].y = top;
        g_quad_vertices[2].y = g_quad_vertices[3].y = g_quad_vertices[1].y + height;
        break;
    case 1:
        top = (entity->position.y + entity->render_offset.y) + entity->base_position.y;
        g_quad_vertices[0].y = g_quad_vertices[1].y = top;
        g_quad_vertices[2].y = g_quad_vertices[3].y =
            ((entity->position.y + entity->render_offset.y) + entity->base_position.y) + height;
        break;
    case 2:
        g_quad_vertices[0].y = g_quad_vertices[1].y =
            (entity->position.y + entity->render_offset.y) + entity->base_position.y - height;
        g_quad_vertices[2].y = g_quad_vertices[3].y =
            (entity->position.y + entity->render_offset.y) + entity->base_position.y;
        break;
    }

    float bottom = entity->render_offset.z + entity->position.z + entity->base_position.z;
    g_quad_vertices[0].z = g_quad_vertices[1].z = g_quad_vertices[2].z = g_quad_vertices[3].z = bottom;

    return manager->SubmitSpriteQuad(entity, 1);
}
#pragma code_seg()
