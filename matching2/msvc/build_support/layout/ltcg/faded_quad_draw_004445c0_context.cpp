// Complete genuine retail graph; none of these helper bodies is selected here.
// The real dispatcher is the link entry, with its public two-stack-argument
// entry in this small native graph. Its complete 232-byte contribution is
// declared honestly; its maintained 216-byte owner remains separate.
#include "../../../src/core/sprtfunc/faded_quad_draw.cpp"

// Full algorithm from src/core/sprtfunc/fun_00444240_00444240.cpp. Only the section
// name and camera-global typed views differ from that maintained source.
#pragma code_seg(".text$06b06projection")
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
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[0], &input[0], &((ProjectionEnvironment*)g_render_stage_active)->viewport,
                                 &((ProjectionEnvironment*)g_render_stage_active)->projection, &((ProjectionEnvironment*)g_render_stage_active)->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[1], &input[1], &((ProjectionEnvironment*)g_render_stage_active)->viewport,
                                 &((ProjectionEnvironment*)g_render_stage_active)->projection, &((ProjectionEnvironment*)g_render_stage_active)->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[2], &input[2], &((ProjectionEnvironment*)g_render_stage_active)->viewport,
                                 &((ProjectionEnvironment*)g_render_stage_active)->projection, &((ProjectionEnvironment*)g_render_stage_active)->view, &world);
    asm_D3DXVec3Project_0045218e(&g_quad_vertices[3], &input[3], &((ProjectionEnvironment*)g_render_stage_active)->viewport,
                                 &((ProjectionEnvironment*)g_render_stage_active)->projection, &((ProjectionEnvironment*)g_render_stage_active)->view, &world);
    manager->projected_world = world;
    return 0;
}
#pragma code_seg()

#include "../../../src/core/sprtfunc/animation_color_multiply_channel.cpp"
#include "../../../src/core/sprtfunc/render_state_sync.cpp"
#include "../../../src/core/sprtfunc/sprite_quad_submit.cpp"
#include "../../../src/core/sprtfunc/anm_batch_flush.cpp"
#include "../../../src/core/sprtfunc/quad_vertex_append.cpp"
#include "../../../src/core/sprtfunc/anm_vm_draw_dispatch.cpp"
