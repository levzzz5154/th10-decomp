// 0x004379E0..0x004379FE: create a texture from the device global, returning
// the created texture rather than the HRESULT.  The height arrives in ECX and
// the width in EDX.
extern "C" int __stdcall D3DXCreateTexture2(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture);
extern "C" void* g_d3d_device;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void* __fastcall CreateTexture(unsigned int height, unsigned int width) {
    void* device = g_d3d_device;
    void* texture;
    D3DXCreateTexture2(device, width, height, 1, 0, 0x19, 1, &texture);
    return texture;
}
#pragma code_seg()
