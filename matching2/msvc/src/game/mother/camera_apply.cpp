// 0x004215A0: apply the camera's view/projection and normalized right vector.
#include "th10/render/camera_batch.hpp"
inline CameraVector* CameraCross(CameraVector* out, const CameraVector* a, const CameraVector* b) {
    CameraVector value;
    value.x = a->y * b->z - a->z * b->y;
    value.y = a->z * b->x - a->x * b->z;
    value.z = a->x * b->y - a->y * b->x;
    *out = value;
    return out;
}
#pragma code_seg(".text$00bcamera")
void RenderCamera::Apply() {
    if (g_sprt_ctrl) g_sprt_ctrl->Flush();
    CameraVector target(direction.x + position.x, direction.y + position.y, direction.z + position.z);
    CameraVector eye(eye_offset.x + position.x, eye_offset.y + position.y, eye_offset.z + position.z);
    CameraLookAt(&view, &eye, &target, &up);
    CameraPerspective(&projection, field_of_view, (float)width / (float)height, 30.0f, 1800.0f);
    typedef long (__stdcall *SetTransform)(void*, unsigned int, const CameraMatrix*);
    RenderDevice* device = g_d3d_device;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 2, &view);
    device = g_d3d_device;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 3, &projection);
    CameraCross(&right, &direction, &up);
    CameraNormalize(&right, &right);
    if (g_sprt_ctrl) {
        ((int*)g_sprt_ctrl)[0x5C / 4] = clip_x;
        ((int*)g_sprt_ctrl)[0x60 / 4] = clip_y;
    }
}
#pragma code_seg()
