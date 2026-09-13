// 0x0043BC40: clear and present twice, resetting the device after each failed present.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$01aclear")
int __stdcall ClearAndPresentTwice(unsigned int color) {
    data_00491c30->Clear(0, 0, 3, color, 1.0f, 0);
    if (data_00491c30->Present(0, 0, 0, 0) < 0)
        data_00491c30->Reset(data_00491d0c);
    data_00491c30->Clear(0, 0, 3, color, 1.0f, 0);
    int result = data_00491c30->Present(0, 0, 0, 0);
    if (result < 0)
        return data_00491c30->Reset(data_00491d0c);
    return result;
}
#pragma code_seg()
