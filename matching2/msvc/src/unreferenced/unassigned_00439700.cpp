#include "../../build_support/layout/ltcg/resource_surface_loading_log.hpp"

extern "C" void* __stdcall Direct3DCreate9_00452176(unsigned sdk_version);
extern "C" void* data_00491c2c;
extern "C" char str_d3d_create_failed[];

// TextLog::AppendLine receives its object in EDI in the native LTCG cluster.
#pragma code_seg(".text$01create")
extern "C" __declspec(noinline) int __cdecl GraphicsInit_00439700() {
    void* device = Direct3DCreate9_00452176(0x20);
    const bool created = device != 0;
    data_00491c2c = device;
    if (!created) {
        g_log.AppendLine(str_d3d_create_failed);
        return 1;
    }
    return 0;
}
#pragma code_seg()
