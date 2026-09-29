#include "th10/render/camera_batch.hpp"
// Camera members begin the two 0x118-byte render-stage records.
extern "C" RenderCamera data_00491d7c;
extern "C" RenderCamera data_00491e94;
// Initialize only the selected camera fields; leave matrices and other state intact.
extern "C" __declspec(noinline) void __cdecl RenderCamera_InitializeDefaults_004216f0() {
    data_00491e94.position = CameraVector(0.0f, 0.0f, 1000.0f);
    data_00491e94.direction = CameraVector(0.0f, 0.0f, 0.0f);
    data_00491e94.up = CameraVector(0.0f, 1.0f, 0.0f);
    data_00491e94.field_of_view = 0.5235988f;
    data_00491e94.viewport_x = 0;
    data_00491e94.viewport_y = 0;
    data_00491e94.width = 640;
    data_00491e94.height = 480;
    data_00491e94.min_z = 0.0f;
    data_00491e94.max_z = 1.0f;
    data_00491e94.unknown_0e4 = 1;
    data_00491e94.eye_offset = CameraVector(0.0f, 0.0f, 0.0f);
    data_00491d7c.position = CameraVector(0.0f, 0.0f, 1000.0f);
    data_00491d7c.direction = CameraVector(0.0f, 0.0f, 0.0f);
    data_00491d7c.up = CameraVector(0.0f, 1.0f, 0.0f);
    data_00491d7c.field_of_view = 0.5235988f;
    data_00491d7c.viewport_x = 32;
    data_00491d7c.viewport_y = 16;
    data_00491d7c.width = 384;
    data_00491d7c.height = 448;
    data_00491d7c.min_z = 0.0f;
    data_00491d7c.max_z = 1.0f;
    data_00491d7c.unknown_0e4 = 0;
    data_00491d7c.eye_offset = CameraVector(0.0f, 0.0f, 0.0f);
}
