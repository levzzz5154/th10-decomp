// 0x004436C0..0x0044390E and 0x00443910..0x00443B3E (591 bytes each): the two
// rotated sprite quad builders.
//
// The entity's in-plane angle (rotation.z) turns its two sprite extents into the
// four corners of the shared sprite quad, which the submit pipeline then
// finishes; an angle of exactly zero hands the quad to the unrotated anchored
// builder instead.  The two regions are one body written twice - their bytes
// differ only in the displacement of the two direct calls - and the dispatcher
// 0x004451C0 reaches both with the manager in ECX and the entity in EDX, tail
// jumping to them (see src/core/sprtfunc/anm_vm_draw_dispatch.cpp).
//
// The field names follow the shared entity layout in include/th10/game/entity
// .hpp: rotation at +0x24 (a Vector3, so the in-plane angle is its z),
// scale_x/scale_y at +0x3C/+0x40, sprite_width/sprite_height at +0x4C/+0x50,
// base_position/position/render_offset at +0x334/+0x340/+0x34C, and the flag
// word at +0x35C.  The extents are sprite_width * scale_x and sprite_height *
// scale_y; the placement is render_offset + position + base_position, in that
// term order.  The two anchor fields of the flag word select the edges:
// (flags >> 18) & 3 for x and (flags >> 20) & 3 for y, each with cases
// centred (-half / +half), left-anchored (0 / size) and right-anchored
// (-size / 0), and the same value used for the two corners of an edge.
//
// The trigonometric pair is the original source's own assembly: no C++ spelling
// on this toolkit emits the combined FSINCOS the bodies use.
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDraw2(RenderEntity* entity,
                                                       SprtCtrlBatchView* manager);

#pragma code_seg(".text$06b03rotquad")
extern "C" __declspec(noinline) int BuildRotatedQuad(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    float ca, sa;
    float angle;
    float px, py, pz, width, height;
    float xs[4], ys[4];

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

    px = entity->render_offset.x + entity->position.x + entity->base_position.x;
    py = entity->render_offset.y + entity->position.y + entity->base_position.y;
    width = entity->sprite_width * entity->scale_x;
    height = entity->sprite_height * entity->scale_y;

    switch ((entity->flags >> 18) & 3) {
    case 0:
        xs[0] = xs[2] = width * -0.5f;
        xs[1] = xs[3] = width * 0.5f;
        break;
    case 1:
        xs[0] = xs[2] = 0.0f;
        xs[1] = xs[3] = width;
        break;
    case 2:
        xs[0] = xs[2] = -width;
        xs[1] = xs[3] = 0.0f;
        break;
    }
    switch ((entity->flags >> 20) & 3) {
    case 0:
        ys[0] = ys[1] = height * -0.5f;
        ys[2] = ys[3] = height * 0.5f;
        break;
    case 1:
        ys[0] = ys[1] = 0.0f;
        ys[2] = ys[3] = height;
        break;
    case 2:
        ys[0] = ys[1] = -height;
        ys[2] = ys[3] = 0.0f;
        break;
    }

    g_quad_vertices[0].x = xs[0] * ca - ys[0] * sa + px;
    g_quad_vertices[0].y = xs[0] * sa + ys[0] * ca + py;
    g_quad_vertices[1].x = xs[1] * ca - ys[1] * sa + px;
    g_quad_vertices[1].y = xs[1] * sa + ys[1] * ca + py;
    g_quad_vertices[2].x = xs[2] * ca - ys[2] * sa + px;
    g_quad_vertices[2].y = xs[2] * sa + ys[2] * ca + py;
    g_quad_vertices[3].x = xs[3] * ca - ys[3] * sa + px;
    g_quad_vertices[3].y = xs[3] * sa + ys[3] * ca + py;

    pz = entity->render_offset.z + entity->position.z + entity->base_position.z;
    g_quad_vertices[3].z = pz;
    g_quad_vertices[2].z = pz;
    g_quad_vertices[1].z = pz;
    g_quad_vertices[0].z = pz;

    return manager->SubmitSpriteQuad(entity, 0);
}
#pragma code_seg()

#pragma code_seg(".text$06b04rotquad")
extern "C" __declspec(noinline) int BuildRotatedQuadAlt(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    float ca, sa;
    float angle;
    float px, py, pz, width, height;
    float xs[4], ys[4];

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

    px = entity->render_offset.x + entity->position.x + entity->base_position.x;
    py = entity->render_offset.y + entity->position.y + entity->base_position.y;
    width = entity->sprite_width * entity->scale_x;
    height = entity->sprite_height * entity->scale_y;

    switch ((entity->flags >> 18) & 3) {
    case 0:
        xs[0] = xs[2] = width * -0.5f;
        xs[1] = xs[3] = width * 0.5f;
        break;
    case 1:
        xs[0] = xs[2] = 0.0f;
        xs[1] = xs[3] = width;
        break;
    case 2:
        xs[0] = xs[2] = -width;
        xs[1] = xs[3] = 0.0f;
        break;
    }
    switch ((entity->flags >> 20) & 3) {
    case 0:
        ys[0] = ys[1] = height * -0.5f;
        ys[2] = ys[3] = height * 0.5f;
        break;
    case 1:
        ys[0] = ys[1] = 0.0f;
        ys[2] = ys[3] = height;
        break;
    case 2:
        ys[0] = ys[1] = -height;
        ys[2] = ys[3] = 0.0f;
        break;
    }

    g_quad_vertices[0].x = xs[0] * ca - ys[0] * sa + px;
    g_quad_vertices[0].y = xs[0] * sa + ys[0] * ca + py;
    g_quad_vertices[1].x = xs[1] * ca - ys[1] * sa + px;
    g_quad_vertices[1].y = xs[1] * sa + ys[1] * ca + py;
    g_quad_vertices[2].x = xs[2] * ca - ys[2] * sa + px;
    g_quad_vertices[2].y = xs[2] * sa + ys[2] * ca + py;
    g_quad_vertices[3].x = xs[3] * ca - ys[3] * sa + px;
    g_quad_vertices[3].y = xs[3] * sa + ys[3] * ca + py;

    pz = entity->render_offset.z + entity->position.z + entity->base_position.z;
    g_quad_vertices[3].z = pz;
    g_quad_vertices[2].z = pz;
    g_quad_vertices[1].z = pz;
    g_quad_vertices[0].z = pz;

    return manager->SubmitSpriteQuad(entity, 0);
}
#pragma code_seg()
