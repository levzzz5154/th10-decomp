#include "th10/render/camera_batch.hpp"
// Camera members begin the two 0x118-byte render-stage records.
extern "C" RenderCamera g_back_camera;
extern "C" RenderCamera g_front_camera;
// Initialize only the selected camera fields; leave matrices and other state intact.
extern "C" __declspec(noinline) void __cdecl RenderCamera_InitializeDefaults() {
    g_front_camera.position = CameraVector(0.0f, 0.0f, 1000.0f);
    g_front_camera.direction = CameraVector(0.0f, 0.0f, 0.0f);
    g_front_camera.up = CameraVector(0.0f, 1.0f, 0.0f);
    g_front_camera.field_of_view = 0.5235988f;
    g_front_camera.viewport_x = 0;
    g_front_camera.viewport_y = 0;
    g_front_camera.width = 640;
    g_front_camera.height = 480;
    g_front_camera.min_z = 0.0f;
    g_front_camera.max_z = 1.0f;
    g_front_camera.unknown_0e4 = 1;
    g_front_camera.eye_offset = CameraVector(0.0f, 0.0f, 0.0f);
    g_back_camera.position = CameraVector(0.0f, 0.0f, 1000.0f);
    g_back_camera.direction = CameraVector(0.0f, 0.0f, 0.0f);
    g_back_camera.up = CameraVector(0.0f, 1.0f, 0.0f);
    g_back_camera.field_of_view = 0.5235988f;
    g_back_camera.viewport_x = 32;
    g_back_camera.viewport_y = 16;
    g_back_camera.width = 384;
    g_back_camera.height = 448;
    g_back_camera.min_z = 0.0f;
    g_back_camera.max_z = 1.0f;
    g_back_camera.unknown_0e4 = 0;
    g_back_camera.eye_offset = CameraVector(0.0f, 0.0f, 0.0f);
}
