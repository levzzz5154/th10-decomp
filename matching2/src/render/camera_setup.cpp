// =============================================================================
// camera_setup.cpp - Camera, default viewport, and back-buffer surface ops
// =============================================================================
#include "th10/render/camera_setup.hpp"

// Semantic reconstruction 0x00421480 - rebuild view/projection matrices.
// camera block and hand both to the device (SetTransform states 2 and 3),
// then publish the clip-rect pointers into the manager.
void Camera_Apply(CameraState* camera, const CameraHooks* hooks) {
    static const float kUp[3] = {0.0f, -1.0f, 0.0f};
    hooks->matrix_look_at_lh(hooks->context, camera->view, camera->eye,
                             camera->at, kUp);
    hooks->matrix_perspective_fov_lh(hooks->context, camera->projection,
                                     camera->fov_y, camera->aspect,
                                     camera->near_plane, camera->far_plane);
    hooks->set_transform(hooks->context, 2, camera->view);
    hooks->set_transform(hooks->context, 3, camera->projection);
    hooks->publish_clip_rect(hooks->context);
}

// Semantic reconstruction 0x0043BCD0 - apply the 640x480 viewport.
// into the caller's six-dword block, apply it, and reset clip state. The
// storage parameter replaces retail's fixed DAT_00491CF4 block.
void Viewport_ApplyDefault(ViewportBlock* storage,
                           const ViewportHooks* hooks) {
    // 0x0043BCD0 opens by flushing the staged sprite batch (0x00442F50)
    // when the manager is live, then fills the six-dword block retail keeps
    // at 0x00491CF4, hands it to SetViewport, and closes with 0x0043BC40.
    if (hooks->flush_sprite_batch != 0)
        hooks->flush_sprite_batch(hooks->context);
    storage->x = 0;
    storage->y = 0;
    storage->width = 0x280;
    storage->height = 0x1E0;
    storage->min_z = 0.0f;
    storage->max_z = 1.0f;
    hooks->set_viewport(hooks->context, storage);
    hooks->reset_clip_state(hooks->context);
}

// 0x00448270 - Surface_CopyBackBufferToSlot: flush pending sprites, then blit
// the current back buffer into the slot texture's level-0 surface with point
// filtering. No-op when the slot has no texture.
int Surface_CopyBackBufferToSlot(int slot_has_texture,
                                 const SurfaceOpHooks* hooks) {
    if (slot_has_texture == 0)
        return -1;
    hooks->flush_sprite_batch(hooks->context);
    if (hooks->get_back_buffer(hooks->context) != 0)
        return -1;
    if (hooks->get_surface_level(hooks->context, 0) != 0)
        return -1;
    int status = hooks->copy_surface(hooks->context, 2); // D3DX_FILTER_POINT
    hooks->release_pair(hooks->context);
    return status;
}

// 0x00448450 - Surface_CreateSnapshotTargets: (re)build the pause-snapshot
// texture and the two offscreen plain surfaces sized to the back buffer,
// then seed both surfaces with the current frame.
int Surface_CreateSnapshotTargets(int slot_exists, unsigned int width,
                                  unsigned int height,
                                  const SurfaceOpHooks* hooks) {
    hooks->flush_sprite_batch(hooks->context);
    if (slot_exists != 0)
        hooks->release_existing(hooks->context, 0);
    if (hooks->get_back_buffer(hooks->context) != 0)
        return -1;
    hooks->store_dimensions(hooks->context, width, height);
    if (hooks->create_texture(hooks->context, 0, width, height) != 0)
        return -1;
    for (int slot = 0; slot < 2; ++slot) {
        if (hooks->create_plain_surface(hooks->context, slot, width,
                                        height) != 0)
            return -1;
        if (hooks->copy_surface(hooks->context, 2) != 0)
            return -1;
    }
    hooks->release_pair(hooks->context);
    return 0;
}
