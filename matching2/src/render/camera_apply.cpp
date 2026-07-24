#include "th10/render/camera_apply.hpp"

// Unsigned-wrap constant added to negative viewport extents before the
// float conversion (retail 0x00470B98 holds 4294967296.0).
extern float DAT_00470b98;

namespace {

// Retail converts the 32-bit extent as unsigned: negative signed values
// wrap by 2^32.
float UnsignedExtent(int32_t value) {
    float result = (float)value;
    if (value < 0) {
        result += DAT_00470b98;
    }
    return result;
}

}  // namespace

// 0x004215A0 - Apply the primary 3D camera. Retail keeps the camera in
// EDI and reads the global game state manager / device; the flush and
// the clip copy are guarded on the manager, reproduced here by the
// nullable manager_clip destination. Call order follows retail: flush,
// view matrix, projection matrix, both SetTransform uploads, right
// vector rebuild, clip copy.
void Camera_ApplyPerspective(GameCamera* camera, float* manager_clip,
                             const CameraApplyHooks* hooks) {
    if (manager_clip != 0 && hooks->flush != 0) {
        hooks->flush();
    }

    float at[3];
    float eye[3];
    at[0] = camera->direction[0] + camera->position[0];
    at[1] = camera->direction[1] + camera->position[1];
    at[2] = camera->direction[2] + camera->position[2];
    eye[0] = camera->eye_offset[0] + camera->position[0];
    eye[1] = camera->eye_offset[1] + camera->position[1];
    eye[2] = camera->eye_offset[2] + camera->position[2];
    hooks->matrix_look_at(camera->view, eye, at, camera->up);

    const float width = UnsignedExtent(camera->viewport_width);
    const float height = UnsignedExtent(camera->viewport_height);
    hooks->matrix_perspective(camera->projection, camera->fov_y,
                              width / height, 30.0f, 1800.0f);

    hooks->set_transform(2, camera->view);        // D3DTS_VIEW
    hooks->set_transform(3, camera->projection);  // D3DTS_PROJECTION

    // right = cross(up, direction), normalized in place.
    camera->right[0] = camera->up[2] * camera->direction[1] -
                       camera->up[1] * camera->direction[2];
    camera->right[1] = camera->up[0] * camera->direction[2] -
                       camera->up[2] * camera->direction[0];
    camera->right[2] = camera->up[1] * camera->direction[0] -
                       camera->up[0] * camera->direction[1];
    if (hooks->vec3_normalize != 0) {
        hooks->vec3_normalize(camera->right, camera->right);
    }

    if (manager_clip != 0) {
        manager_clip[0] = camera->clip_x;
        manager_clip[1] = camera->clip_y;
    }
}
