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
extern "C" __declspec(noinline) int EntityDraw_00443080(RenderEntity* entity,
                                                       AnimationManager_00442F50* manager) {
    float width = entity->sprite_width * entity->scale_x;
    float height = entity->sprite_height * entity->scale_y;
    float half_height = height * 0.5f;
    float left, top;

    switch ((entity->flags >> 18) & 3) {
    case 0:
        left = (float)floor(entity->render_offset.x + entity->position.x
                            + entity->base_position.x - width * 0.5f);
        data_004978c0[0].x = data_004978c0[2].x = left;
        data_004978c0[1].x = data_004978c0[3].x = data_004978c0[2].x + width;
        break;
    case 1:
        left = entity->base_position.x + entity->position.x + entity->render_offset.x;
        data_004978c0[0].x = data_004978c0[2].x = left;
        data_004978c0[1].x = data_004978c0[3].x =
            entity->base_position.x + entity->position.x + width + entity->render_offset.x;
        break;
    case 2:
        data_004978c0[0].x = data_004978c0[2].x =
            entity->base_position.x + entity->position.x + entity->render_offset.x - width;
        data_004978c0[1].x = data_004978c0[3].x =
            entity->base_position.x + entity->position.x + entity->render_offset.x;
        break;
    }

    switch ((entity->flags >> 20) & 3) {
    case 0:
        top = (float)floor(entity->render_offset.y + entity->position.y
                           + entity->base_position.y - half_height);
        data_004978c0[0].y = data_004978c0[1].y = top;
        data_004978c0[2].y = data_004978c0[3].y = data_004978c0[1].y + height;
        break;
    case 1:
        top = (entity->position.y + entity->render_offset.y) + entity->base_position.y;
        data_004978c0[0].y = data_004978c0[1].y = top;
        data_004978c0[2].y = data_004978c0[3].y =
            ((entity->position.y + entity->render_offset.y) + entity->base_position.y) + height;
        break;
    case 2:
        data_004978c0[0].y = data_004978c0[1].y =
            (entity->position.y + entity->render_offset.y) + entity->base_position.y - height;
        data_004978c0[2].y = data_004978c0[3].y =
            (entity->position.y + entity->render_offset.y) + entity->base_position.y;
        break;
    }

    float bottom = entity->render_offset.z + entity->position.z + entity->base_position.z;
    data_004978c0[0].z = data_004978c0[1].z = data_004978c0[2].z = data_004978c0[3].z = bottom;

    return manager->SubmitSpriteQuad(entity, 1);
}
#pragma code_seg()
