// =============================================================================
// camera_setup.hpp - Camera + viewport application (retail 0x00421480,
//                    0x0043BCD0) and back-buffer surface ops (0x00448270,
//                    0x00448450)
// =============================================================================
#ifndef TH10_RENDER_CAMERA_SETUP_HPP
#define TH10_RENDER_CAMERA_SETUP_HPP

struct CameraState {
    float eye[3];        // ctx+0xD4 scaled by _DAT_00470B0C
    float at[3];         // ctx+0xD8 block
    float view[16];      // ctx+0x4C
    float projection[16];// ctx+0x8C
    float fov_y;         // 0x3EA0D97C (~0.314159 rad * ...)
    float aspect;
    float near_plane;    // 1.0f
    float far_plane;     // 10000.0f
};

struct CameraHooks {
    void* context;
    void (*matrix_look_at_lh)(void* context, float* out, const float* eye,
                              const float* at, const float* up);
    void (*matrix_perspective_fov_lh)(void* context, float* out, float fov_y,
                                      float aspect, float near_plane,
                                      float far_plane);
    void (*set_transform)(void* context, int state, const float* matrix);
    // Publish the clip rect pointers into the manager (+0x5C/+0x60).
    void (*publish_clip_rect)(void* context);
};

void Camera_Apply(CameraState* camera, const CameraHooks* hooks);

struct ViewportBlock {
    unsigned int x, y, width, height;
    float min_z, max_z;
};

struct ViewportHooks {
    void* context;
    void (*set_viewport)(void* context, const ViewportBlock* viewport);
    void (*reset_clip_state)(void* context); // 0x0043BC40
};

// storage: caller-provided six-dword block (retail DAT_00491CF4).
void Viewport_ApplyDefault(ViewportBlock* storage, const ViewportHooks* hooks);

struct SurfaceOpHooks {
    void* context;
    void (*flush_sprite_batch)(void* context);        // 0x00442F50
    int (*get_back_buffer)(void* context);            // vtable +0x48
    int (*get_surface_level)(void* context, int slot);
    int (*copy_surface)(void* context, int filter);   // D3DXLoadSurfaceFromSurface
    void (*release_pair)(void* context);
    void (*release_existing)(void* context, int slot);// 0x00447F70
    int (*create_texture)(void* context, int slot, unsigned int width,
                          unsigned int height);       // vtable +0x70
    int (*create_plain_surface)(void* context, int slot, unsigned int width,
                                unsigned int height); // vtable +0x90
    void (*store_dimensions)(void* context, unsigned int width,
                             unsigned int height);    // mgr+0x3AD6E0/E4
};

int Surface_CopyBackBufferToSlot(int slot_has_texture,
                                 const SurfaceOpHooks* hooks);
int Surface_CreateSnapshotTargets(int slot_exists, unsigned int width,
                                  unsigned int height,
                                  const SurfaceOpHooks* hooks);

#endif // TH10_RENDER_CAMERA_SETUP_HPP
