#pragma once

#include <cstdint>

// External math/device edges used by the camera apply path. Retail
// binds these to D3DX imports and the device vtable.
struct CameraApplyHooks {
    // 0x00442F50 staged-geometry flush; only invoked when the game
    // state manager exists.
    void (*flush)();
    // D3DXMatrixLookAtLH(out, eye, at, up)
    void (*matrix_look_at)(float* out, const float* eye, const float* at,
                           const float* up);
    // D3DXMatrixPerspectiveFovLH(out, fov_y, aspect, near_z, far_z)
    void (*matrix_perspective)(float* out, float fov_y, float aspect,
                               float near_z, float far_z);
    // IDirect3DDevice9::SetTransform(state, matrix) (device vtable +0xB0)
    void (*set_transform)(uint32_t state_id, const float* matrix);
    // D3DXVec3Normalize(out, in)
    void (*vec3_normalize)(float* out, const float* in);
};

// Camera block (retail 32-bit word offsets in comments; matches the
// block reset by Camera_ResetDefaults at 0x004216F0).
struct GameCamera {
    float position[3];      // words 0x00..0x02
    float direction[3];     // words 0x03..0x05, at-target offset
    float up[3];            // words 0x06..0x08
    float reserved_24[3];   // words 0x09..0x0B
    float right[3];         // words 0x0C..0x0E, recomputed cross product
    float eye_offset[3];    // words 0x0F..0x11, shake/eye displacement
    float fov_y;            // word 0x12
    float view[16];         // words 0x13..0x22, view matrix out
    float projection[16];   // words 0x23..0x32
    uint32_t reserved_cc[2];  // words 0x33..0x34
    int32_t viewport_width;   // word 0x35, unsigned-wrapped to float
    int32_t viewport_height;  // word 0x36
    uint32_t reserved_dc[3];  // words 0x37..0x39
    float clip_x;             // word 0x3A, copied to the manager
    float clip_y;             // word 0x3B
};

// 0x004215A0 - Apply the primary 3D camera: flush staged geometry,
// rebuild the view matrix from position + eye offset / position +
// direction / up, rebuild the projection from the unsigned-wrapped
// viewport extent (near 30.0, far 1800.0), upload both transforms
// (state ids 2 and 3), recompute the normalized right vector as
// cross(up, direction), and copy the clip pair into the manager's
// clip words (retail manager+0x5C/+0x60) when a manager exists.
void Camera_ApplyPerspective(GameCamera* camera, float* manager_clip,
                             const CameraApplyHooks* hooks);
