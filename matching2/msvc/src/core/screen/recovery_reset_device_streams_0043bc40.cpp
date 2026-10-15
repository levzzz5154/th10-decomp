// 0x0043BC40: clear and present twice, resetting the device after each failed present.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$01aclear")
int __stdcall ClearAndPresentTwice(unsigned int color) {
    g_d3d_device->Clear(0, 0, 3, color, 1.0f, 0);
    if (g_d3d_device->Present(0, 0, 0, 0) < 0)
        g_d3d_device->Reset(data_00491d0c);
    g_d3d_device->Clear(0, 0, 3, color, 1.0f, 0);
    int result = g_d3d_device->Present(0, 0, 0, 0);
    if (result < 0)
        return g_d3d_device->Reset(data_00491d0c);
    return result;
}
#pragma code_seg()
