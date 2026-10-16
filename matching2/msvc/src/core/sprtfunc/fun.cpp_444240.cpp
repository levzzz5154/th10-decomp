// 0x00444240: rebuild one projected entity's world matrix and project the four
// corners of its anchor quad.
//
// The entity arrives in EAX and the manager on the stack, with the callee
// popping it; no C++ prototype can declare that entry convention, so the body
// is compiled inside the native-LTCG cluster
// build_support/layout/ltcg/entity_quad_projection.json (driver and layout gaps are
// never selected as game code).

struct ProjectionMatrix2 {
    float m[16];
};

struct ProjectionVec32 {
    float x, y, z;
};

struct D3DViewport {
    unsigned int x, y, width, height;
    float min_z, max_z;
};

// The camera state global the projection pipeline reads: two matrices followed
// by the active D3D viewport.
struct ProjectionEnvironment {
    unsigned char reserved_000[0x4C];
    ProjectionMatrix2 view;        // +0x4C
    ProjectionMatrix2 projection;  // +0x8C
    D3DViewport viewport;         // +0xCC
};

// One entry of the shared sprite quad the projection writes into.
struct ProjectedVertex {
    float x, y, z, rhw;
    unsigned int color;
    float u, v;
};

extern "C" ProjectedVertex g_quad_vertices[4];
extern "C" ProjectionEnvironment* g_render_stage_active;

// The compiler's pooled double 0.0 the three rotation guards compare against.
extern "C" double dbl_0;

struct ProjectionManager {
    unsigned char reserved_00000000[0x3AD0F0];
    ProjectionMatrix2 projected_world;  // +0x3AD0F0
};

struct ProjectedEntity {
    unsigned char reserved_00000000[0x24];
    float rotation_x;               // +0x24
    float rotation_y;               // +0x28
    float rotation_z;               // +0x2C
    unsigned char reserved3[0x3C - 0x30];
    float scale_x;                  // +0x3C
    float scale_y;                  // +0x40
    unsigned char reserved4[0x23C - 0x44];
    ProjectionMatrix2 source_matrix;  // +0x23C
    ProjectionMatrix2 world_matrix;   // +0x27C
    unsigned char reserved5[0x334 - 0x2BC];
    ProjectionVec32 offset_position;  // +0x334
    ProjectionVec32 layer_position;   // +0x340
    ProjectionVec32 base_position;    // +0x34C
    float unknown4;                   // +0x358
    unsigned int flags;                       // +0x35C

    __declspec(noinline) int ProjectQuad(ProjectionManager* manager);
};

// The D3DX entry thunks at 0x45218E/0x4521AC..0x4521BE; their targets pop the
// arguments, so every call site is a plain stdcall with no cleanup.
extern "C" void __stdcall asm_D3DXMatrixRotationX_004521ac(ProjectionMatrix2* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationY_004521b8(ProjectionMatrix2* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationZ_004521be(ProjectionMatrix2* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixMultiply_004521b2(ProjectionMatrix2* out,
                                                          const ProjectionMatrix2* left,
                                                          const ProjectionMatrix2* right);
extern "C" void __stdcall asm_D3DXVec3Project_0045218e(void* out, const void* vector,
                                                       const D3DViewport* viewport,
                                                       const ProjectionMatrix2* projection,
                                                       const ProjectionMatrix2* view,
                                                       const ProjectionMatrix2* world);

#pragma code_seg(".text$01quadx")
int ProjectedEntity::ProjectQuad(ProjectionManager* manager) {
    if ((flags & 0x4000u) == 0 && (flags & 0x0Cu) != 0) {
        world_matrix = source_matrix;
        world_matrix.m[0] *= scale_x;
        world_matrix.m[5] *= scale_y;
        flags &= 0xFFFFFFF7u;
        ProjectionMatrix2 rotation;
        if (rotation_x != dbl_0) {
            asm_D3DXMatrixRotationX_004521ac(&rotation, rotation_x);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        if (rotation_y != dbl_0) {
            asm_D3DXMatrixRotationY_004521b8(&rotation, rotation_y);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        if (rotation_z != dbl_0) {
            asm_D3DXMatrixRotationZ_004521be(&rotation, rotation_z);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        flags &= 0xFFFFFFFBu;
    }
    ProjectionVec32 input[4];
    ProjectionMatrix2 world = world_matrix;
    world.m[12] = base_position.x + layer_position.x + offset_position.x + world.m[12];
    world.m[13] = base_position.y + layer_position.y + offset_position.y + world.m[13];
    world.m[14] = base_position.z + layer_position.z + offset_position.z;
    switch ((flags >> 18) & 3u) {
    case 0:
        input[0].x = input[2].x = -128.0f;
        input[1].x = input[3].x = 128.0f;
        break;
    case 1:
        input[0].x = input[2].x = 0.0f;
        input[1].x = input[3].x = 256.0f;
        break;
    case 2:
        input[0].x = input[2].x = -256.0f;
        input[1].x = input[3].x = 0.0f;
        break;
    }
    switch ((flags >> 20) & 3u) {
    case 0:
        input[0].y = input[1].y = -128.0f;
        input[2].y = input[3].y = 128.0f;
        break;
    case 1:
        input[0].y = input[1].y = 0.0f;
        input[2].y = input[3].y = 256.0f;
        break;
    case 2:
        input[0].y = input[1].y = -256.0f;
        input[2].y = input[3].y = 0.0f;
        break;
    }
    input[0].z = input[1].z = input[2].z = input[3].z = 0.0f;
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[0], &input[0], &g_render_stage_active->viewport,
                                 &g_render_stage_active->projection, &g_render_stage_active->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[1], &input[1], &g_render_stage_active->viewport,
                                 &g_render_stage_active->projection, &g_render_stage_active->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[2], &input[2], &g_render_stage_active->viewport,
                                 &g_render_stage_active->projection, &g_render_stage_active->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[3], &input[3], &g_render_stage_active->viewport,
                                 &g_render_stage_active->projection, &g_render_stage_active->view, &world);
    manager->projected_world = world;
    return 0;
}
#pragma code_seg()
