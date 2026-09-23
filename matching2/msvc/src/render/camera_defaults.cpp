#include "th10/render/camera_batch.hpp"

// The two 0x118-byte render-stage records begin at 0x00491D7C and
// 0x00491E94.  Their camera members occupy the first 0xF0 bytes of each
// record; this routine initializes selected fields and leaves the matrices
// and other camera state untouched.
extern "C" RenderCamera data_00491d7c;
extern "C" RenderCamera data_00491e94;

// Ghidra identifies this as a no-argument leaf. The old assembly label stays
// available as a raw alias for its naked caller.
extern "C" __declspec(noinline) void __cdecl RenderCamera_InitializeDefaults_004216f0() {
    RenderCamera& first_stage_camera = data_00491d7c;
    first_stage_camera.position.x = 0.0f;
    first_stage_camera.position.y = 0.0f;
    first_stage_camera.position.z = 1000.0f;
    first_stage_camera.direction.x = 0.0f;
    first_stage_camera.direction.y = 0.0f;
    first_stage_camera.direction.z = 0.0f;
    first_stage_camera.up.x = 0.0f;
    first_stage_camera.up.y = 1.0f;
    first_stage_camera.up.z = 0.0f;
    first_stage_camera.eye_offset.x = 0.0f;
    first_stage_camera.eye_offset.y = 0.0f;
    first_stage_camera.eye_offset.z = 0.0f;
    first_stage_camera.field_of_view = 0.5235988f; // 0x3F060A92
    first_stage_camera.viewport_x = 32;
    first_stage_camera.viewport_y = 16;
    first_stage_camera.width = 384;
    first_stage_camera.height = 448;
    first_stage_camera.min_z = 0.0f;
    first_stage_camera.max_z = 1.0f;
    first_stage_camera.unknown_0e4 = 0;

    RenderCamera& second_stage_camera = data_00491e94;
    second_stage_camera.position.x = 0.0f;
    second_stage_camera.position.y = 0.0f;
    second_stage_camera.position.z = 1000.0f;
    second_stage_camera.direction.x = 0.0f;
    second_stage_camera.direction.y = 0.0f;
    second_stage_camera.direction.z = 0.0f;
    second_stage_camera.up.x = 0.0f;
    second_stage_camera.up.y = 1.0f;
    second_stage_camera.up.z = 0.0f;
    second_stage_camera.eye_offset.x = 0.0f;
    second_stage_camera.eye_offset.y = 0.0f;
    second_stage_camera.eye_offset.z = 0.0f;
    second_stage_camera.field_of_view = 0.5235988f; // 0x3F060A92
    second_stage_camera.viewport_x = 0;
    second_stage_camera.viewport_y = 0;
    second_stage_camera.width = 640;
    second_stage_camera.height = 480;
    second_stage_camera.min_z = 0.0f;
    second_stage_camera.max_z = 1.0f;
    second_stage_camera.unknown_0e4 = 1;
}
