#ifndef TH10_STAGE_OBJECTS_HPP
#define TH10_STAGE_OBJECTS_HPP
#include <stddef.h>
#include "th10/game/game_thread_text.hpp"
#include "th10/math/timer.hpp"

// A position with the arithmetic the stage code uses.
struct StageVector : RenderVec3 {
    StageVector() {}
    StageVector(float px, float py, float pz) { x = px; y = py; z = pz; }
    StageVector operator+(const StageVector& rhs) const { return StageVector(x + rhs.x, y + rhs.y, z + rhs.z); }
    StageVector operator-(const StageVector& rhs) const { return StageVector(x - rhs.x, y - rhs.y, z - rhs.z); }
    StageVector operator*(float factor) const { return StageVector(x * factor, y * factor, z * factor); }
};
inline void WorldIdentity(CameraMatrix* matrix) {
    matrix->m[1] = matrix->m[2] = matrix->m[3] = matrix->m[4] = matrix->m[6] = matrix->m[7] =
        matrix->m[8] = matrix->m[9] = matrix->m[11] = matrix->m[12] = matrix->m[13] = matrix->m[14] = 0.0f;
    matrix->m[0] = matrix->m[5] = matrix->m[10] = matrix->m[15] = 1.0f;
}
// One quad of a stage background object. The list ends at a negative type,
// and each record gives its own byte size.
struct StageQuad {
    short type;
    short size;
    short script;
    short entity;                          // index of the animation entity that draws it
    RenderVec3 position;                   // relative to the instance
    float width;                           // 0 keeps the sprite's own size
    float height;
};
// A stage background object: a bounding box and the quads inside it.
struct StageObject {
    short id;
    signed char layer;
    unsigned char flags;                   // bit 1: drawn this frame
    StageVector center;
    StageVector size;
    StageQuad quads[1];

    // 0x00403090: 1 when the box, moved by `offset`, is too far from the
    // camera or projects outside the playfield.
    __declspec(noinline) int IsOutsideView(const StageVector* offset, const RenderCamera* camera,
                                           float max_distance_squared) const;
};
// One placement of an object in the stage. The list ends at a negative object.
struct StageInstance {
    short object;
    short reserved;
    StageVector position;
};
struct StageSprite {
    unsigned char reserved_00[0x30];
    float height;
    float width;
};
// The animation entities the quads draw with, 0x3AC bytes each.
struct StageEntity : RenderEntity {
    unsigned char reserved_398[0x3AC - sizeof(RenderEntity)];
};
struct StageObjects {
    unsigned char reserved_0000[0x14];
    StageObject** objects;                 // +0x14
    StageInstance* instances;              // +0x18
    unsigned char reserved_001c[0x17C - 0x1C];
    StageEntity* entities;                 // +0x17C
    StageEntity sprites[8];                // +0x180, drawn flat behind the objects
    float max_distance_squared;            // +0x1EE0
    int sprite_frames;                     // +0x1EE4, counts frames once it is nonzero
    unsigned int fade_color;               // +0x1EE8, alpha in the top byte
    int dimmed;                            // +0x1EEC, draw the sprites darkened
    unsigned char reserved_1ef0[0x2A0C - 0x1EF0];
    int drawn_objects;                     // +0x2A0C
    int culled_objects;                    // +0x2A10
    int drawn_quads;                       // +0x2A14
    unsigned int flags;                    // +0x2A18: 1 objects, 2 hide after the fade, 4 fading, 8 hidden
    FrameTimer fade_timer;                 // +0x2A1C
    FrameTimer clear_timer;                // +0x2A30
    unsigned char reserved_2a44[0x2A4C - 0x2A44];
    GameThreadRenderStage view;            // +0x2A4C, the stage camera and fog
};
typedef char StageObjectsView[(offsetof(StageObjects, view) == 0x2A4C) ? 1 : -1];
typedef char StageObjectsTimer[(offsetof(StageObjects, fade_timer) == 0x2A1C) ? 1 : -1];
typedef char StageObjectQuads[(offsetof(StageObject, quads) == 0x1C) ? 1 : -1];
typedef char StageQuadSize[(sizeof(StageQuad) == 0x1C) ? 1 : -1];
typedef char StageInstanceSize[(sizeof(StageInstance) == 0x10) ? 1 : -1];
typedef char StageObjectsCounters[(offsetof(StageObjects, drawn_quads) == 0x2A14) ? 1 : -1];
typedef char StageEntitySize[(sizeof(StageEntity) == 0x3AC) ? 1 : -1];

extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
    AnimationManager_00442F50*, RenderEntity*);
extern "C" CameraMatrix* __stdcall D3DXMatrixTranslation(CameraMatrix*, float, float, float);
extern "C" RenderVec3* __stdcall D3DXVec3ProjectArray(
    RenderVec3* out, unsigned int out_stride, const RenderVec3* in, unsigned int in_stride,
    const unsigned int* viewport, const CameraMatrix* projection, const CameraMatrix* view,
    const CameraMatrix* world, unsigned int count);

extern "C" __declspec(noinline) int __cdecl asm_AnimationManager_RenderBucket_00448980(
    void* manager, int index);

// Flush the sprite batch, then change one device render state.
inline void StageSetRenderState(unsigned int state, unsigned int value) {
    data_00491c10->Flush();
    data_00491c30->State(state, value);
}
// Switch device fog (render state 0x1C) unless it already has that setting.
inline void StageSetFog(int enabled) {
    if (data_00491c28.fog_enabled != enabled) {
        data_00491c10->Flush();
        data_00491c28.fog_enabled = enabled;
        data_00491c30->State(0x1C, enabled);
    }
}

__declspec(noinline) int __stdcall StageObjects_DrawLayer(StageObjects* stage, int layer);
__declspec(noinline) int __stdcall StageObjects_Draw(StageObjects* stage);
__declspec(noinline) int __stdcall StageObjects_DrawBackground(StageObjects* stage);
#endif
