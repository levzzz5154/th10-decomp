// 0x00444240: rebuild one projected entity's world matrix and project the four
// corners of its anchor quad.
//
// The entity arrives in EAX and the manager on the stack, with the callee
// popping it; no C++ prototype can declare that entry convention, so the body
// is compiled inside the native-LTCG cluster
// build_support/layout/ltcg/entity_quad_projection_00444240.json (driver and layout gaps are
// never selected as game code).

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

extern "C" ProjectedVertex_00444240 data_004978c0[4];
extern "C" ProjectionEnvironment_00444240* data_00491fac;

// The compiler's pooled double 0.0 the three rotation guards compare against.
extern "C" double data_00470b70;

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

#pragma code_seg(".text$01quadx")
int ProjectedEntity_00444240::ProjectQuad(ProjectionManager_00444240* manager) {
    if ((flags & 0x4000u) == 0 && (flags & 0x0Cu) != 0) {
        world_matrix = source_matrix;
        world_matrix.m[0] *= scale_x;
        world_matrix.m[5] *= scale_y;
        flags &= 0xFFFFFFF7u;
        ProjectionMatrix_00444240 rotation;
        if (rotation_x != data_00470b70) {
            asm_D3DXMatrixRotationX_004521ac(&rotation, rotation_x);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        if (rotation_y != data_00470b70) {
            asm_D3DXMatrixRotationY_004521b8(&rotation, rotation_y);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        if (rotation_z != data_00470b70) {
            asm_D3DXMatrixRotationZ_004521be(&rotation, rotation_z);
            asm_D3DXMatrixMultiply_004521b2(&world_matrix, &world_matrix, &rotation);
        }
        flags &= 0xFFFFFFFBu;
    }
    ProjectionVec3_00444240 input[4];
    ProjectionMatrix_00444240 world = world_matrix;
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
    asm_D3DXVec3Project_0045218e(&data_004978c0[0], &input[0], &data_00491fac->viewport,
                                 &data_00491fac->projection, &data_00491fac->view, &world);
    asm_D3DXVec3Project_0045218e(&data_004978c0[1], &input[1], &data_00491fac->viewport,
                                 &data_00491fac->projection, &data_00491fac->view, &world);
    asm_D3DXVec3Project_0045218e(&data_004978c0[2], &input[2], &data_00491fac->viewport,
                                 &data_00491fac->projection, &data_00491fac->view, &world);
    asm_D3DXVec3Project_0045218e(&data_004978c0[3], &input[3], &data_00491fac->viewport,
                                 &data_00491fac->projection, &data_00491fac->view, &world);
    manager->projected_world = world;
    return 0;
}
#pragma code_seg()
