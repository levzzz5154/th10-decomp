// 0x0043BCD0: restore the full depth-range viewport, then clear/present both buffers.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$01capply")
__declspec(noinline) int __stdcall ApplyDefaultViewport(unsigned int color) {
    if (g_sprt_ctrl)
        g_sprt_ctrl->Flush();
    g_device_viewport.x = 0;
    g_device_viewport.y = 0;
    g_device_viewport.width = 640;
    g_device_viewport.height = 480;
    g_device_viewport.min_z = 0.0f;
    g_device_viewport.max_z = 1.0f;
    g_d3d_device->Viewport(&g_device_viewport);
    return ClearAndPresentTwice(color);
}
#pragma code_seg()
