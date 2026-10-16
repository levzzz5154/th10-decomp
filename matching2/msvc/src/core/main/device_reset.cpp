#include "th10/source_views/device_reset_24c334_0.hpp"
extern "C" __declspec(noinline) void __cdecl DeviceReset2() {
    char filename[256];
    if (g_d3d_device->methods->Present(g_d3d_device,0,0,0,0)<0) {
        g_sprt_ctrl->ReleaseTargets();
        g_d3d_device->methods->Reset(g_d3d_device,g_present_parameters);
        Renderer_ApplyDeviceDefaults();
        g_device_mode=2;
    }
    g_sprt_ctrl->FinishTargets();
    if (g_input_keys_held&0x800U) {
        MakeDirectory(str_snapshot_dir);
        int index;
        for (index=0;index<1000;++index) {
            FormatString(filename,str_snapshot_path_format,index);
            if (!FileProbe(filename)) break;
        }
        if (index>=1000) return;
        if (index<1000) g_application.CaptureScreenshot(filename);
    }
}
