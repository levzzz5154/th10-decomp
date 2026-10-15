// 0x00443B60 - build the four projected screen vertices of a billboard quad.
//
// The billboard centre and the camera reference point are projected through a
// world matrix that is the identity translated by the sum of the three position
// layers. The screen-space distance between both projections scales the quad's
// extents, the two anchor fields of the flags word select the two edges of each
// axis, and the in-plane rotation turns those corners into the shared vertex
// array. A centre outside the normalized depth range rejects the quad.

#include <math.h>

struct ProjectionVec3 { float x, y, z; };
struct ProjectionVertex { float x, y, z, rhw; unsigned int color; float u, v; };
struct ProjectionMatrix { float m[16]; };

// The render target whose view, projection and viewport matrices feed the
// projection, plus the reference point the perspective scale is measured
// against.
struct ProjectionDevice_00443B60 {
    unsigned char unknown_0000[0x30];
    ProjectionVec3 reference;              // 0x30
    unsigned char unknown_003C[0x10];
    float view[16];                        // 0x4C
    float projection[16];                  // 0x8C
    float viewport[6];                     // 0xCC
};

// The shared .rdata float constants, read through their retail addresses.
extern "C" float data_00470b04;            //  0.0f
extern "C" float data_00470afc;            //  1.0f
extern "C" float data_00470b0c;            //  0.5f
extern "C" float data_00470b78;            // -0.5f

extern "C" ProjectionDevice_00443B60* data_00491fac;
extern "C" ProjectionVertex g_quad_vertices[4];

// The projection helper the renderer reaches through its own import stub.
extern "C" int __stdcall D3DXVec3Project(void* out, const void* in, const void* viewport,
                                         const void* projection, const void* view,
                                         const void* world);

struct BillboardSource_00443B60 {
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
int BillboardSource_00443B60::BuildProjectedQuad() {
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
    float xs[4], ys[4];

    // Retail keeps the trigonometric pair in inline assembly: for sin/cos of one
    // value the compiler emits an FSIN/FCOS pair, never the combined FSINCOS the
    // renderer's projection uses.
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

    D3DXVec3Project(&center, &origin, &data_00491fac->viewport, &data_00491fac->projection,
                    &data_00491fac->view, &world);
    if (center.z < 0.0f || center.z > 1.0f)
        return -1;
    D3DXVec3Project(&reference, &data_00491fac->reference, &data_00491fac->viewport,
                    &data_00491fac->projection, &data_00491fac->view, &world);

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

    // (flags >> 18) & 3 anchors the two horizontal corners, (flags >> 20) & 3
    // the vertical ones. The two-valued cases leave the fourth corner in the
    // floating-point register the retail body keeps it in.
    switch ((this->flags >> 18) & 3) {
    case 0:
        xs[0] = xs[2] = extent_x * -0.5f;
        xs[1] = xs[3] = extent_x * 0.5f;
        break;
    case 1:
        xs[0] = xs[2] = 0.0f;
        xs[1] = xs[3] = extent_x;
        break;
    case 2:
        xs[0] = xs[2] = -extent_x;
        xs[1] = xs[3] = 0.0f;
        break;
    }
    switch ((this->flags >> 20) & 3) {
    case 0:
        ys[0] = ys[1] = extent_y * -0.5f;
        ys[2] = ys[3] = extent_y * 0.5f;
        break;
    case 1:
        ys[0] = ys[1] = 0.0f;
        ys[2] = ys[3] = extent_y;
        break;
    case 2:
        ys[0] = ys[1] = -extent_y;
        ys[2] = ys[3] = 0.0f;
        break;
    }

    g_quad_vertices[0].x = xs[0] * ca - ys[0] * sa + center_x;
    g_quad_vertices[0].y = xs[0] * sa + ys[0] * ca + center_y;
    g_quad_vertices[1].x = xs[1] * ca - ys[1] * sa + center_x;
    g_quad_vertices[1].y = xs[1] * sa + ys[1] * ca + center_y;
    g_quad_vertices[2].x = xs[2] * ca - ys[2] * sa + center_x;
    g_quad_vertices[2].y = xs[2] * sa + ys[2] * ca + center_y;
    g_quad_vertices[3].x = xs[3] * ca - ys[3] * sa + center_x;
    g_quad_vertices[3].y = xs[3] * sa + ys[3] * ca + center_y;
    return 0;
}
#pragma code_seg()
