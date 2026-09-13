// 0x0043BCD0: restore the full depth-range viewport, then clear/present both buffers.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$00capply")
__declspec(noinline) int __stdcall ApplyDefaultViewport(unsigned int color) {
    if (data_00491c10)
        data_00491c10->Flush();
    data_00491cf4.x = 0;
    data_00491cf4.y = 0;
    data_00491cf4.width = 640;
    data_00491cf4.height = 480;
    data_00491cf4.min_z = 0.0f;
    data_00491cf4.max_z = 1.0f;
    data_00491c30->Viewport(&data_00491cf4);
    return ClearAndPresentTwice(color);
}
#pragma code_seg()
