// 0x00421480: construct a centered perspective view from the viewport dimensions.
//
// The viewport's width and height are converted once, kept in memory, and the
// ratio is materialised at the definition because the camera's perspective
// matrix reads it after the view matrix call.  `*(volatile float*)&aspect` is a
// measured code-generation lever, not recovered style: it is the only spelling
// that makes the /O2 generator store the quotient where retail stores it
// instead of keeping it in an x87 register to the call.
#include "th10/render/camera_batch.hpp"
#include <math.h>
extern "C" const double data_00470ba0;
#pragma code_seg(".text$00adefault")
void RenderCamera::ApplyDefault() {
    if (data_00491c10) data_00491c10->Flush();
    float viewport_width = (float)width;
    float half_width = viewport_width * 0.5f;
    float viewport_height = (float)height;
    float half_height = viewport_height * 0.5f;
    float aspect;
    *(volatile float*)&aspect = viewport_width / viewport_height;
    CameraVector view_up, target, eye;
    eye.x = half_width; eye.y = half_height; eye.z = half_height / (float)tan(data_00470ba0);
    target.x = half_width; target.y = half_height; target.z = 0.0f;
    view_up.x = 0.0f; view_up.y = -1.0f; view_up.z = 0.0f;
    CameraLookAt(&view, &eye, &target, &view_up);
    CameraPerspective(&projection, 0.31415927f, aspect, 1.0f, 10000.0f);
    typedef long (__stdcall *SetTransform)(void*, unsigned int, const CameraMatrix*);
    RenderDevice* device = data_00491c30;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 2, &view);
    device = data_00491c30;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 3, &projection);
    if (data_00491c10) {
        ((int*)data_00491c10)[0x5C / 4] = clip_x;
        ((int*)data_00491c10)[0x60 / 4] = clip_y;
    }
}
#pragma code_seg()
