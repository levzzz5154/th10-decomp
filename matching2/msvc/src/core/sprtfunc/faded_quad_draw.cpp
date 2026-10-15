// 0x004445C0..0x00444751: project an animation entity's quad, transform its
// four fade probes, and attenuate RGB by distance while preserving alpha.
// Submit mode 2, then restore the four shared RHW values to one.
//
// Retail and this native link use manager/entity on the stack and RET 8.
// The dedicated driver contains only genuine complete helper implementations
// and the real draw dispatcher; only this 402-byte body is selected here.
#include "th10/render/quad_batch.hpp"
#include <math.h>

// Genuine projection helper's complete object views. The dedicated driver
// defines its unchanged projection algorithm with compatible views of the
// shared vertex/camera globals and a layout-specific contribution name.
struct ProjectionMatrix_00444240 {
    float m[16];
};

struct ProjectionVec3_00444240 {
    float x, y, z;
};

struct D3DViewport_00444240 {
    unsigned int x, y, width, height;
    float min_z, max_z;
};

// The camera state global the projection pipeline reads: two matrices followed
// by the active D3D viewport.
struct ProjectionEnvironment_00444240 {
    unsigned char reserved_000[0x4C];
    ProjectionMatrix_00444240 view;        // +0x4C
    ProjectionMatrix_00444240 projection;  // +0x8C
    D3DViewport_00444240 viewport;         // +0xCC
};

// One entry of the shared sprite quad the projection writes into.
struct ProjectedVertex_00444240 {
    float x, y, z, rhw;
    unsigned int color;
    float u, v;
};

// The compiler's pooled double 0.0 the three rotation guards compare against.
extern "C" double dbl_0;

struct ProjectionManager_00444240 {
    unsigned char reserved_00000000[0x3AD0F0];
    ProjectionMatrix_00444240 projected_world;  // +0x3AD0F0
};

struct ProjectedEntity_00444240 {
    unsigned char reserved_00000000[0x24];
    float rotation_x;               // +0x24
    float rotation_y;               // +0x28
    float rotation_z;               // +0x2C
    unsigned char reserved_00000030[0x3C - 0x30];
    float scale_x;                  // +0x3C
    float scale_y;                  // +0x40
    unsigned char reserved_00000044[0x23C - 0x44];
    ProjectionMatrix_00444240 source_matrix;  // +0x23C
    ProjectionMatrix_00444240 world_matrix;   // +0x27C
    unsigned char reserved_000002BC[0x334 - 0x2BC];
    ProjectionVec3_00444240 offset_position;  // +0x334
    ProjectionVec3_00444240 layer_position;   // +0x340
    ProjectionVec3_00444240 base_position;    // +0x34C
    float unknown_00000358;                   // +0x358
    unsigned int flags;                       // +0x35C

    __declspec(noinline) int ProjectQuad(ProjectionManager_00444240* manager);
};

// The D3DX entry thunks at 0x45218E/0x4521AC..0x4521BE; their targets pop the
// arguments, so every call site is a plain stdcall with no cleanup.
extern "C" void __stdcall asm_D3DXMatrixRotationX_004521ac(ProjectionMatrix_00444240* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationY_004521b8(ProjectionMatrix_00444240* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationZ_004521be(ProjectionMatrix_00444240* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixMultiply_004521b2(ProjectionMatrix_00444240* out,
                                                          const ProjectionMatrix_00444240* left,
                                                          const ProjectionMatrix_00444240* right);
extern "C" void __stdcall asm_D3DXVec3Project_0045218e(void* out, const void* vector,
                                                       const D3DViewport_00444240* viewport,
                                                       const ProjectionMatrix_00444240* projection,
                                                       const ProjectionMatrix_00444240* view,
                                                       const ProjectionMatrix_00444240* world);

// The published world matrix and the four fade probes it was built from live in
// the animation manager; this view names only the two spans this body reads.
struct FadeMatrix_004445C0 { float m[16]; };
struct FadeProbe_004445C0 { float x, y, z, u, v; };
struct FadeProbe4_004445C0 { float x, y, z, w; };
struct FadeManagerView_004445C0 {
    unsigned char reserved_003AD0F0[0x3AD0F0];
    FadeMatrix_004445C0 projected_world;                 // +0x3AD0F0
    unsigned char reserved_003AD130[0x3ADA78 - 0x3AD130];
    FadeProbe_004445C0 probes[4];                        // +0x3ADA78
};

// The camera focus at 0x491D7C, the near/far distances at 0x491E78, the fade
// colour channels at 0x491E80 and the packed fade colour at 0x491E90.
extern "C" float data_00491d7c;
extern "C" float data_00491d80;
extern "C" float data_00491d84;
extern "C" float data_00491e78;
extern "C" float data_00491e7c;
extern "C" float data_00491e80;
extern "C" float data_00491e84;
extern "C" float data_00491e88;
extern "C" unsigned int data_00491e90;

// The D3DX entry thunk at 0x4521C4; it jumps to the imported D3DXVec3Transform,
// which pops its own three arguments.
extern "C" void __stdcall D3DXVec3Transform_004521c4(FadeProbe4_004445C0* out,
                                                     const float* vector,
                                                     const FadeMatrix_004445C0* matrix);

static __forceinline float DistanceFrom_004445C0(float dx, float dy, float dz) {
    return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

#pragma code_seg(".text$06b0800fadequad")
extern "C" __declspec(noinline) int FadedQuadDraw_004445c0(SprtCtrlBatchView* manager,
                                                           RenderEntity* entity) {
    FadeManagerView_004445C0* view = (FadeManagerView_004445C0*)manager;
    ((ProjectedEntity_00444240*)entity)->ProjectQuad((ProjectionManager_00444240*)manager);
    float span = data_00491e78 - data_00491e7c;
    unsigned int color = (entity->flags & 0x8000u) ? entity->color_secondary : entity->color;
    FadeProbe4_004445C0 projected[4];
    // Traverse packed colors by their alpha-byte address, at one vertex stride.
    // Keep a signed integer sentinel so it never forms a pointer past the quad.
    int color_cursor = (int)&g_quad_vertices[0].color + 3;
    int color_end = color_cursor + sizeof(g_quad_vertices);
    for (int i = 0; color_cursor < color_end; ++i, color_cursor += sizeof(TexturedVertex)) {
        unsigned char* out = (unsigned char*)(color_cursor - 3);
        D3DXVec3Transform_004521c4(&projected[i], &view->probes[i].x, &view->projected_world);
        float dx = projected[i].x - data_00491d7c;
        float dy = projected[i].y - data_00491d80;
        float dz = projected[i].z - data_00491d84;
        float distance = DistanceFrom_004445C0(dx, dy, dz);
        if (data_00491e78 < distance) {
            float fade = (data_00491e78 - distance) / span;
            if (fade >= 1.0f) {
                *(unsigned int*)out = data_00491e90;
                out[3] = ((unsigned char*)&color)[3];
            } else {
                out[0] = (unsigned char)(((unsigned char*)&color)[0]
                        - (unsigned char)(int)(((float)((unsigned char*)&color)[0]
                                                - data_00491e80) * fade));
                out[1] = (unsigned char)(((unsigned char*)&color)[1]
                        - (unsigned char)(int)(((float)((unsigned char*)&color)[1]
                                                - data_00491e84) * fade));
                unsigned short tail = *(const unsigned short*)((const unsigned char*)&color + 2);
                out[2] = (unsigned char)((unsigned char)tail
                        - (unsigned char)(int)(((float)(unsigned char)tail - data_00491e88) * fade));
                out[3] = (unsigned char)(tail >> 8);
            }
        } else {
            *(unsigned int*)out = color;
        }
    }
    int result = manager->SubmitSpriteQuad(entity, 2);
    g_quad_vertices[3].rhw = 1.0f;
    g_quad_vertices[2].rhw = 1.0f;
    g_quad_vertices[1].rhw = 1.0f;
    g_quad_vertices[0].rhw = 1.0f;
    return result;
}
#pragma code_seg()
