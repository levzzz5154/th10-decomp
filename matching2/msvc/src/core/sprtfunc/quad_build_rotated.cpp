// 0x004436C0 and 0x00443910: two native entries for the same rotated sprite.
// With zero rotation, use the anchored builder. Otherwise rotate the four
// anchored corners about the sprite origin and submit them as a textured quad.
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDraw2(RenderEntity* entity, SprtCtrlBatchView* manager);

static __forceinline int SubmitRotatedCorners(SprtCtrlBatchView* manager, RenderEntity* entity,
                                               float cosine, float sine) {
    float px, py, pz, width, height;

    px = entity->render_offset.x + entity->position.x + entity->base_position.x;
    py = entity->render_offset.y + entity->position.y + entity->base_position.y;
    width = entity->sprite_width * entity->scale_x;
    height = entity->sprite_height * entity->scale_y;

    WriteAnchoredSpriteCorners(entity->flags, width, height, cosine, sine, px, py);

    pz = entity->render_offset.z + entity->position.z + entity->base_position.z;
    g_quad_vertices[3].z = pz;
    g_quad_vertices[2].z = pz;
    g_quad_vertices[1].z = pz;
    g_quad_vertices[0].z = pz;

    return manager->SubmitSpriteQuad(entity, 0);
}

// MATCH: retail uses x87 FSINCOS; MSVC 7.1 emits separate sin/cos intrinsics
// for C++ calls, so both rotated entry points share this helper.
static __forceinline int BuildRotatedQuadBody(SprtCtrlBatchView* manager, RenderEntity* entity) {
    float ca, sa;
    float angle;

    if (entity->rotation.z == 0.0f) {
        return EntityDraw2(entity, manager);
    }

    angle = entity->rotation.z;
    __asm {
        fld angle
        fsincos
        fstp ca
        fstp sa
    }

    return SubmitRotatedCorners(manager, entity, ca, sa);
}

#pragma code_seg(".text$06b03rotquad")
extern "C" __declspec(noinline) int BuildRotatedQuad(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    return BuildRotatedQuadBody(manager, entity);
}
#pragma code_seg()

#pragma code_seg(".text$06b04rotquad")
extern "C" __declspec(noinline) int BuildRotatedQuadAlt(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    return BuildRotatedQuadBody(manager, entity);
}
#pragma code_seg()
