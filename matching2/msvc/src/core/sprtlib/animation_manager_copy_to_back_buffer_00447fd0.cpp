// 0x00447FD0 (330 bytes): copy a loaded image surface onto the back buffer.
// The image is kept in system memory; the first copy creates a device-side
// surface for it (a render target, or an offscreen plain surface when that
// fails) and fills it from the image. The blit takes the image's rectangle
// from (left, top) to its full size and lands it at (x, y).
//
// Native LTCG passes the manager in EBX and the index in EAX; the four
// coordinates stay on the stack. Nothing in the retail image calls it.
#include "th10/render/resource_surface_loading.hpp"

// The device is always reached through this accessor: it makes the compiler
// load the device and its vtable before the arguments, as retail does.
static inline SurfaceDevice_00447c80* Device() { return g_d3d_device; }

#pragma code_seg(".text$03copy")
void AnimationManagerIndexed_00447f70::CopyToBackBuffer(int index, int left, int top, int x, int y) {
    if (!secondary[index])
        return;
    ResourceView* back_buffer;
    if (Device()->GetBackBuffer(0, 0, 0, &back_buffer) != 0)
        return;
    if (!primary[index]) {
        if (Device()->CreateRenderTarget(info[index].width, info[index].height, g_render_target_format,
                                              0, 0, 1, &primary[index], 0) != 0 &&
            Device()->CreateOffscreenPlainSurface(info[index].width, info[index].height,
                                                       g_render_target_format, 3, &primary[index], 0) != 0) {
            back_buffer->Release();
            return;
        }
        if (LoadSurfaceCopy_004521d6(primary[index], 0, 0, secondary[index], 0, 0, 1, 0) != 0) {
            back_buffer->Release();
            return;
        }
    }
    SurfaceRect_00447fd0 rect;
    rect.left = left;
    rect.top = top;
    rect.right = info[index].width;
    rect.bottom = info[index].height;
    SurfacePoint_00447fd0 point;
    point.x = x;
    point.y = y;
    Device()->UpdateSurface(primary[index], &rect, back_buffer, &point);
    back_buffer->Release();
}
#pragma code_seg()
