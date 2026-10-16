// 0x00443480..0x00443678 (505 bytes): build one anchored sprite quad for the
// mirrored submit.
//
// The twin of 0x00443290, with three differences: an entity that is not
// visible (flags 1 and 2, non-zero alpha) is rejected with -1, both extents
// are halved (so the "centred" case spans half the sprite either way and the
// anchored cases span twice the half extent), and the finished quad goes to
// the texture-mirroring submit with pixel snapping (mode 1).
//
// Nothing in the game calls this body. The entity arrives in EAX and the
// manager on the stack (the callee pops it).
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDrawMirrored(RenderEntity *entity,
                                                                SprtCtrlBatchView *manager);
#pragma code_seg(".text$06b02z02mirror")
int EntityDrawMirrored(RenderEntity *entity, SprtCtrlBatchView *manager) {
    if (!(entity->flags & 1))
        return -1;
    if (!(entity->flags & 2))
        return -1;
    if (!reinterpret_cast<const unsigned char *>(&entity->color)[3])
        return -1;

    float half_width = entity->sprite_width * entity->scale_x * 0.5f;
    float half_height = entity->sprite_height * entity->scale_y * 0.5f;
    switch ((entity->flags >> 18) & 3) {
    case 0: {
        float left = entity->position.x;
        left = left + entity->render_offset.x;
        left = left + entity->base_position.x;
        g_quad_vertices[0].x = g_quad_vertices[2].x = left - half_width;
        float right = entity->position.x;
        right = right + entity->render_offset.x;
        right = right + entity->base_position.x;
        g_quad_vertices[1].x = g_quad_vertices[3].x = right + half_width;
        break;
    }
    case 1: {
        float left = entity->position.x;
        left = left + entity->render_offset.x;
        left = left + entity->base_position.x;
        g_quad_vertices[0].x = g_quad_vertices[2].x = left;
        float right = half_width + half_width;
        right = right + entity->position.x;
        right = right + entity->render_offset.x;
        right = right + entity->base_position.x;
        g_quad_vertices[1].x = g_quad_vertices[3].x = right;
        break;
    }
    case 2: {
        float left = entity->position.x;
        left = left + entity->render_offset.x;
        left = left + entity->base_position.x;
        left = left - half_width;
        left = left - half_width;
        g_quad_vertices[0].x = g_quad_vertices[2].x = left;
        float right = entity->position.x;
        right = right + entity->render_offset.x;
        right = right + entity->base_position.x;
        g_quad_vertices[1].x = g_quad_vertices[3].x = right;
        break;
    }
    }
    switch ((entity->flags >> 20) & 3) {
    case 0: {
        float top = entity->position.y;
        top = top + entity->render_offset.y;
        top = top + entity->base_position.y;
        g_quad_vertices[0].y = g_quad_vertices[1].y = top - half_height;
        float bottom = entity->position.y;
        bottom = bottom + entity->render_offset.y;
        bottom = bottom + half_height;
        bottom = bottom + entity->base_position.y;
        g_quad_vertices[2].y = g_quad_vertices[3].y = bottom;
        break;
    }
    case 1: {
        float top = entity->position.y;
        top = top + entity->render_offset.y;
        top = top + entity->base_position.y;
        g_quad_vertices[0].y = g_quad_vertices[1].y = top;
        float bottom = half_height + half_height;
        bottom = bottom + entity->position.y;
        bottom = bottom + entity->render_offset.y;
        bottom = bottom + entity->base_position.y;
        g_quad_vertices[2].y = g_quad_vertices[3].y = bottom;
        break;
    }
    case 2: {
        float top = entity->position.y;
        top = top + entity->render_offset.y;
        top = top + entity->base_position.y;
        top = top - half_height;
        top = top - half_height;
        g_quad_vertices[0].y = g_quad_vertices[1].y = top;
        float bottom = entity->position.y;
        bottom = bottom + entity->render_offset.y;
        bottom = bottom + entity->base_position.y;
        g_quad_vertices[2].y = g_quad_vertices[3].y = bottom;
        break;
    }
    }
    float z = entity->render_offset.z + entity->position.z + entity->base_position.z;
    g_quad_vertices[3].z = z;
    g_quad_vertices[2].z = z;
    g_quad_vertices[1].z = z;
    g_quad_vertices[0].z = z;
    return manager->SubmitSpriteQuadMirrored(entity, 1);
}
#pragma code_seg()
