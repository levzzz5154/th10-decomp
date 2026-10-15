#include "th10/source_views/device_reset_24c334_0.hpp"
extern "C" __declspec(noinline) void __cdecl DeviceReset_004391f0() {
    char filename[256];
    if (g_d3d_device->methods->Present(g_d3d_device,0,0,0,0)<0) {
        g_sprt_ctrl->ReleaseTargets();
        g_d3d_device->methods->Reset(g_d3d_device,data_00491d0c);
        Renderer_ApplyDeviceDefaults();
        data_00491fd4=2;
    }
    g_sprt_ctrl->FinishTargets();
    if (data_00474e36&0x800U) {
        MakeDirectory_00452abc(data_0046f6e4);
        int index;
        for (index=0;index<1000;++index) {
            FormatString_00452ae8(filename,data_0046f6d0,index);
            if (!FileProbe_0044b4d0(filename)) break;
        }
        if (index>=1000) return;
        if (index<1000) g_application.CaptureScreenshot(filename);
    }
}
