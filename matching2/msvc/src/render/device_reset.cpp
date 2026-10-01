#include "th10/render/native_render_targets.hpp"
#include "game_render_targets.cpp"
#pragma code_seg(".text$a06device")
extern "C" __declspec(noinline) void __cdecl DeviceReset_004391f0() {
    char filename[256];
    if (data_00491c30->methods->Present(data_00491c30,0,0,0,0)<0) {
        data_00491c10->ReleaseTargets();
        data_00491c30->methods->Reset(data_00491c30,data_00491d0c);
        Renderer_ApplyDeviceDefaults();
        data_00491fd4=2;
    }
    data_00491c10->FinishTargets();
    if (data_00474e36&0x800U) {
        MakeDirectory_00452abc(data_0046f6e4);
        int index;
        for (index=0;index<1000;++index) {
            FormatString_00452ae8(filename,data_0046f6d0,index);
            if (!FileProbe_0044b4d0(filename)) break;
        }
        if (index>=1000) return;
        if (index<1000) data_00491c28.CaptureScreenshot(filename);
    }
}
#pragma code_seg()
