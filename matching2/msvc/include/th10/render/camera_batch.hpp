#ifndef TH10_CAMERA_BATCH_HPP
#define TH10_CAMERA_BATCH_HPP
#include "th10/render/quad_batch.hpp"
struct CameraVector {
    float x, y, z;
    CameraVector() {}
    CameraVector(float px, float py, float pz) : x(px), y(py), z(pz) {}
};
struct CameraMatrix { float m[16]; };
struct RenderCamera {
    CameraVector position, direction, up, unknown_024, right, eye_offset;
    float field_of_view;
    CameraMatrix view, projection;
    unsigned int viewport_x, viewport_y, width, height;
    float min_z, max_z;
    int unknown_0e4, clip_x, clip_y;
    __declspec(noinline) void Apply();
    __declspec(noinline) void ApplyDefault();
};
extern "C" CameraMatrix* __stdcall CameraLookAt(CameraMatrix*, const CameraVector*, const CameraVector*, const CameraVector*);
extern "C" CameraMatrix* __stdcall CameraPerspective(CameraMatrix*, float, float, float, float);
extern "C" CameraVector* __stdcall CameraNormalize(CameraVector*, const CameraVector*);
#endif
