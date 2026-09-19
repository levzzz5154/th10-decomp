// 0x00443FB0..0x00444233 (643 bytes): distance-fade one animation entity's
// quad and submit it.
//
// The dispatcher reaches this routine with the entity in EDI and the manager in
// ESI, which no declaration names, so the body is a selected function of the
// render-batch cluster (layout/ltcg/anm_batch_flush_00442f50.json).  Both
// callees enter on registers no prototype expresses either - the billboard
// projection takes its source in EAX with no arguments, and the quad projection
// takes its source in EAX with the manager pushed on the stack - so their
// bodies are co-compiled as ABI anchors placed at their retail addresses; see
// the anchor block of layout/ltcg/render_batch_context.cpp.
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

struct ProjectionManager_00444240;
struct ProjectedEntity_00444240 {
    unsigned char reserved_0000[0x334];
    __declspec(noinline) int ProjectQuad(ProjectionManager_00444240* manager);
};

struct BillboardSource_00443B60 {
    unsigned char reserved_0000[0x35C];
    __declspec(noinline) int BuildProjectedQuad();
};

extern "C" float data_00491d7c;
extern "C" float data_00491d80;
extern "C" float data_00491d84;
extern "C" float data_00491e78;
extern "C" float data_00491e7c;
extern "C" float data_00491e80;
extern "C" float data_00491e84;
extern "C" float data_00491e88;

static __forceinline float DistanceFrom_00443FB0(RenderVec3 delta) {
    return (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

#pragma code_seg(".text$06b0600distance")
extern "C" __declspec(noinline) int EntityDraw_00443fb0(AnimationManager_00442F50* manager,
                                                        RenderEntity* entity) {
    if (((BillboardSource_00443B60*)entity)->BuildProjectedQuad() != 0) {
        return -1;
    }
    float span = data_00491e78 - data_00491e7c;
    unsigned int color = (entity->flags & 0x8000u) ? entity->color_secondary : entity->color;
    RenderVec3 delta;
    delta.x = entity->position.x + entity->base_position.x;
    delta.y = entity->position.y + entity->base_position.y;
    delta.z = entity->position.z + entity->base_position.z;
    RenderVec3 t;
    t.x = delta.x + entity->render_offset.x;
    t.y = delta.y + entity->render_offset.y;
    t.z = delta.z + entity->render_offset.z;
    delta.x = t.x - data_00491d7c;
    delta.y = t.y - data_00491d80;
    delta.z = t.z - data_00491d84;
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
    if (data_00491e78 < distance) {
        float fade = (data_00491e78 - distance) / span;
        if (fade >= 1.0f) {
            return -1;
        }
        unsigned char* out = (unsigned char*)&data_004978c0[0].color;
        out[0] = (unsigned char)(((unsigned char*)&color)[0]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[0]
                                                                - (int)data_00491e80) * fade));
        out[1] = (unsigned char)(((unsigned char*)&color)[1]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[1]
                                                                - (int)data_00491e84) * fade));
        out[2] = (unsigned char)(((unsigned char*)&color)[2]
                                 - (unsigned char)(int)((float)(((unsigned char*)&color)[2]
                                                                - (int)data_00491e88) * fade));
        out[3] = (unsigned char)(int)((1.0f - fade) * (float)((unsigned char*)&color)[3]);
    } else {
        data_004978c0[0].color = color;
    }
    data_004978c0[1].color = data_004978c0[0].color;
    data_004978c0[2].color = data_004978c0[0].color;
    data_004978c0[3].color = data_004978c0[0].color;
    return manager->SubmitSpriteQuad(entity, 2);
}
#pragma code_seg()
