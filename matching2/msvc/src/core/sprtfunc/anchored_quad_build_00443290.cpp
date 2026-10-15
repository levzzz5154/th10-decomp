// 0x00443290..0x00443575 (486 bytes): build one anchored sprite quad.
//
// The unrotated sibling of 0x004436C0.  The entity's placement
// (entity->render_offset + entity->position + entity->base_position) and its two sprite extents
// (entity->sprite_width * entity->scale_x, entity->sprite_height * entity->scale_y) turn into the shared quad's
// four edges: the two flag fields (entity->flags >> 18) & 3 and (entity->flags >> 20) & 3 anchor
// x and y independently, each with a centred case (placement -/+ half the
// extent), an anchored case using the placement itself and one using
// `placement - extent`, and the finished quad goes to the submit pipeline with
// mode 0.
//
// Retail enters this body with the entity in EAX and the manager on the stack
// (the callee pops it), which is what its two callers supply - the dispatcher
// 0x004451C0 (`push ecx; call 0x00443290`) and the rotated builders
// 0x004436C0/0x00443910 (`push ecx; mov eax,edx; call 0x00443290`) - so the
// body is modelled as a member of the entity and kept in the render-batch
// cluster where the whole-program pass can pick that pair.
//
// The y switch's four edges are written as separate stepwise accumulations
// rather than one expression per edge, and that is what fixes the last eight
// bytes of the region.  Every y sum starts with render_offset.y (0x350) and then
// uses base_position.y (0x338) before position.y (0x344).  Writing the edge as a
// single expression shares one pair node between the edges of a case, and a pair
// node with more than one use is emitted in ascending struct-offset order
// (0x338, 0x350) whatever the source order; the linear spelling is emitted
// (0x344, 0x350, 0x338).  Neither reaches retail's order for any spelling -
// every parenthesisation, permutation and cast of `(0x350 + 0x338) + 0x344` was
// tried, and a materialised pair local reuses ST(0) instead of recomputing the
// loads.  Giving each chain its own single-use accumulator keeps the source
// order, which is retail's: 0x350, 0x338, 0x344 for both edges of case 1 and for
// the lower edge of case 2, 0x350, 0x338, height, 0x344 for case 1's far edge,
// and 0x350, 0x338, 0x344 - height for case 2's near edge.
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDraw_00443290(RenderEntity* entity,
                                                       SprtCtrlBatchView* manager);
#pragma code_seg(".text$06b02z00build")
int EntityDraw_00443290(RenderEntity* entity, SprtCtrlBatchView* manager) {
    float width = entity->sprite_width * entity->scale_x;
    float height = entity->sprite_height * entity->scale_y;
    float half_height = height * 0.5f;
    float left, right, top, bottom;

    switch ((entity->flags >> 18) & 3) {
    case 0:
        left = entity->render_offset.x + entity->position.x + entity->base_position.x - width * 0.5f;
        data_004978c0[0].x = data_004978c0[2].x = left;
        data_004978c0[1].x = data_004978c0[3].x = data_004978c0[2].x + width;
        break;
    case 1:
        left = (entity->base_position.x + entity->position.x) + entity->render_offset.x;
        data_004978c0[0].x = data_004978c0[2].x = left;
        data_004978c0[1].x = data_004978c0[3].x =
            width + entity->base_position.x + entity->position.x + entity->render_offset.x;
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
        top = entity->render_offset.y + entity->position.y + entity->base_position.y - half_height;
        data_004978c0[0].y = data_004978c0[1].y = top;
        data_004978c0[2].y = data_004978c0[3].y = data_004978c0[1].y + height;
        break;
    case 1: {
        float near = entity->render_offset.y;
        near = near + entity->base_position.y;
        near = near + entity->position.y;
        data_004978c0[0].y = data_004978c0[1].y = near;
        float far = entity->render_offset.y;
        far = far + entity->base_position.y;
        far = far + height;
        far = far + entity->position.y;
        data_004978c0[2].y = data_004978c0[3].y = far;
        break; }
    case 2: {
        float near = entity->render_offset.y;
        near = near + entity->base_position.y;
        near = near + entity->position.y;
        data_004978c0[0].y = data_004978c0[1].y = near - height;
        float far = entity->render_offset.y;
        far = far + entity->base_position.y;
        far = far + entity->position.y;
        data_004978c0[2].y = data_004978c0[3].y = far;
        break; }
    }

    // The original reads the third vector's *y* component here, not its z: the
    // body's z placement is [0x350] + [0x348] + [0x33C], and 0x354 is never
    // touched by this function.  The two siblings (0x00443080, 0x004436C0) do
    // read 0x354, so this is this body's own quirk and it is reproduced.
    bottom = entity->render_offset.y + entity->position.z + entity->base_position.z;
    data_004978c0[3].z = bottom;
    data_004978c0[2].z = bottom;
    data_004978c0[1].z = bottom;
    data_004978c0[0].z = bottom;

    return manager->SubmitSpriteQuad(entity, 0);
}
#pragma code_seg()
