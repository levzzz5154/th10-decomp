// 0x00443B60 - build the four projected screen vertices of a billboard quad.
//
// The billboard centre and the camera reference point are projected through a
// world matrix that is the identity translated by the sum of the three position
// layers. The screen-space distance between both projections scales the quad's
// extents, the two anchor fields of the flags word select the two edges of each
// axis, and the in-plane rotation turns those corners into the shared vertex
// array. A centre outside the normalized depth range rejects the quad.

#include "th10/render/textured_quad.hpp"
#include <math.h>

struct ProjectionVec3 { float x, y, z; };
struct ProjectionMatrix { float m[16]; };

// The render target whose view, projection and viewport matrices feed the
// projection, plus the reference point the perspective scale is measured
// against.
struct ProjectionDevice {
    unsigned char unknown_0000[0x30];
    ProjectionVec3 reference;              // 0x30
    unsigned char unknown_003C[0x10];
    float view[16];                        // 0x4C
    float projection[16];                  // 0x8C
    float viewport[6];                     // 0xCC
};

extern "C" ProjectionDevice* g_render_stage_active;

// The projection helper the renderer reaches through its own import stub.
extern "C" int __stdcall D3DXVec3Project(void* out, const void* in, const void* viewport,
                                         const void* projection, const void* view,
                                         const void* world);

struct BillboardSource {
    unsigned char unknown_0000[0x2C];
    float rotation;                        // 0x2C
    unsigned char unknown_0030[0x0C];
    float size_x;                          // 0x3C
    float size_y;                          // 0x40
    unsigned char unknown_0044[0x08];
    float scale_x;                         // 0x4C
    float scale_y;                         // 0x50
    unsigned char unknown_0054[0x334 - 0x54];
    ProjectionVec3 position;               // 0x334
    ProjectionVec3 offset;                 // 0x340
    ProjectionVec3 layer;                  // 0x34C
    unsigned char unknown_0358[0x04];
    unsigned int flags;                    // 0x35C

    __declspec(noinline) int BuildProjectedQuad();
};

// Half the length of the projected reference offset; the source's own scales
// widen it into the quad's extents. Passing the vector by value is what keeps
// its three components in the retail call's stack copy.
static __forceinline float ProjectionQuad_HalfDistance(ProjectionVec3 delta) {
    return (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) * 0.5f;
}

#pragma code_seg(".text$02quad")
int BillboardSource::BuildProjectedQuad() {
    float ca, sa;
    float extent_y, extent_x;
    ProjectionVec3 origin;
    ProjectionVec3 center;
    float center_x, center_y;
    float angle;
    ProjectionVec3 reference;
    ProjectionMatrix world;
    ProjectionVec3 delta;
    float half;

    // Both native sites use FSINCOS; the pinned compiler emits separate
    // instructions for the C++ sine and cosine intrinsics.
    angle = this->rotation;
    __asm {
        fld angle
        fsincos
        fstp ca
        fstp sa
    }

    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;

    world.m[8] = world.m[9] = world.m[11] = 0.0f;
    world.m[4] = world.m[6] = world.m[7] = 0.0f;
    world.m[1] = world.m[2] = world.m[3] = 0.0f;
    world.m[12] = this->layer.x + this->offset.x + this->position.x;
    world.m[13] = this->layer.y + this->offset.y + this->position.y;
    world.m[14] = this->layer.z + this->offset.z + this->position.z;
    world.m[15] = 1.0f;
    world.m[0] = world.m[5] = world.m[10] = 1.0f;

    D3DXVec3Project(&center, &origin, &g_render_stage_active->viewport, &g_render_stage_active->projection,
                    &g_render_stage_active->view, &world);
    if (center.z < 0.0f || center.z > 1.0f)
        return -1;
    D3DXVec3Project(&reference, &g_render_stage_active->reference, &g_render_stage_active->viewport,
                    &g_render_stage_active->projection, &g_render_stage_active->view, &world);

    delta.x = reference.x - center.x;
    delta.y = reference.y - center.y;
    delta.z = reference.z - center.z;
    half = ProjectionQuad_HalfDistance(delta);
    center_x = center.x;
    center_y = center.y;
    extent_x = this->scale_x * this->size_x * half;
    extent_y = this->scale_y * this->size_y * half;

    g_quad_vertices[3].z = center.z;
    g_quad_vertices[2].z = center.z;
    g_quad_vertices[1].z = center.z;
    g_quad_vertices[0].z = center.z;

    __asm {
        fld angle
        fsincos
        fstp ca
        fstp sa
    }

    WriteAnchoredSpriteCorners(flags, extent_x, extent_y, ca, sa, center_x, center_y);
    return 0;
}
#pragma code_seg()
