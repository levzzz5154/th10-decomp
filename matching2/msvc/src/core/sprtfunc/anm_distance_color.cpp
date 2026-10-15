// 0x00443FB0..0x00444233 (643 bytes): distance-fade one animation entity's
// quad and submit it.
//
// The dispatcher reaches this routine with the entity in EDI and the manager in
// ESI, which no declaration names, so the body is a selected function of the
// render-batch cluster (build_support/layout/ltcg/anm_batch_flush_00442f50.json).  Both
// callees enter on registers no prototype expresses either - the billboard
// projection takes its source in EAX with no arguments, and the quad projection
// takes its source in EAX with the manager pushed on the stack - so their
// bodies are co-compiled as ABI anchors placed at their retail addresses; see
// the anchor block of build_support/layout/ltcg/render_batch_context.cpp.
//
// Four source shapes are load-bearing, not cosmetic, and each was found by
// bisecting the emitted code against retail's:
//
//   * `span` is folded before the colour select, so the `fld`/`fsub` pair is
//     scheduled into the `test ah,ah` shadow exactly as retail's is;
//   * the three `position + base` pairs are summed into `delta` first and the
//     render offset only then added, into `t`, which is what makes the x87
//     stack hold all three sums at once and spill the z one;
//   * `delta` receives the focus subtraction, so the pre-subtraction sums live
//     in `t`'s slots and the deltas in `delta`'s own - retail's two frames;
//   * the faded colour is written bytewise into the shared quad while the
//     un-faded colour is stored whole in the other arm, which is the only form
//     that lets the store sink past the distance compare the way retail's does.
//     (Retail without the fade is the same quad with the colour copied
//     unmodified, so the two arms are equivalent.)
#include "th10/render/quad_batch.hpp"
#include <math.h>

struct ProjectionManager;
struct ProjectedEntity {
    unsigned char reserved_0000[0x334];
    __declspec(noinline) int ProjectQuad(ProjectionManager* manager);
};

struct BillboardSource {
    unsigned char reserved_0000[0x35C];
    __declspec(noinline) int BuildProjectedQuad();
};

extern "C" float g_back_camera;
extern "C" float g_back_camera_2;
extern "C" float g_back_camera_3;
extern "C" float g_sprite_fade_near;
extern "C" float g_sprite_fade_far;
extern "C" float g_sprite_fade_color_r;
extern "C" float g_sprite_fade_color_g;
extern "C" float g_sprite_fade_color_b;

static __forceinline float DistanceFrom_00443FB0(RenderVec3 delta) {
    return (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

#pragma code_seg(".text$06b0600distance")
extern "C" __declspec(noinline) int EntityDraw_00443fb0(SprtCtrlBatchView* manager,
                                                        RenderEntity* entity) {
    if (((BillboardSource*)entity)->BuildProjectedQuad() != 0) {
        return -1;
    }
    float span = g_sprite_fade_near - g_sprite_fade_far;
    unsigned int color = (entity->flags & 0x8000u) ? entity->color_secondary : entity->color;
    RenderVec3 delta;
    delta.x = entity->position.x + entity->base_position.x;
    delta.y = entity->position.y + entity->base_position.y;
    delta.z = entity->position.z + entity->base_position.z;
    RenderVec3 t;
    t.x = delta.x + entity->render_offset.x;
    t.y = delta.y + entity->render_offset.y;
    t.z = delta.z + entity->render_offset.z;
    delta.x = t.x - g_back_camera;
    delta.y = t.y - g_back_camera_2;
    delta.z = t.z - g_back_camera_3;
    float distance = DistanceFrom_00443FB0(delta);
    if (manager->fade_enabled) {
        unsigned char* channel = (unsigned char*)&color;
        unsigned int scaled = (unsigned int)(channel[2] * manager->fade_red) >> 7;
        channel[2] = scaled >= 0x100 ? 0xFF : scaled;
        scaled = (unsigned int)(channel[1] * manager->fade_green) >> 7;
        channel[1] = scaled >= 0x100 ? 0xFF : scaled;
        scaled = (unsigned int)(channel[0] * manager->fade_blue) >> 7;
        channel[0] = scaled >= 0x100 ? 0xFF : scaled;
        scaled = (unsigned int)(channel[3] * manager->fade_alpha) >> 7;
        channel[3] = scaled >= 0x100 ? 0xFF : scaled;
    }
    if (g_sprite_fade_near < distance) {
        float fade = (g_sprite_fade_near - distance) / span;
        if (fade >= 1.0f) {
            return -1;
        }
        unsigned char* out = (unsigned char*)&g_quad_vertices[0].color;
        out[0] = (unsigned char)(((unsigned char*)&color)[0]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[0]
                                                                - (int)g_sprite_fade_color_r) * fade));
        out[1] = (unsigned char)(((unsigned char*)&color)[1]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[1]
                                                                - (int)g_sprite_fade_color_g) * fade));
        out[2] = (unsigned char)(((unsigned char*)&color)[2]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[2]
                                                                - (int)g_sprite_fade_color_b) * fade));
        out[3] = (unsigned char)(int)((1.0f - fade) * (float)((unsigned char*)&color)[3]);
    } else {
        g_quad_vertices[0].color = color;
    }
    g_quad_vertices[1].color = g_quad_vertices[0].color;
    g_quad_vertices[2].color = g_quad_vertices[0].color;
    g_quad_vertices[3].color = g_quad_vertices[0].color;
    return manager->SubmitSpriteQuad(entity, 2);
}
#pragma code_seg()
