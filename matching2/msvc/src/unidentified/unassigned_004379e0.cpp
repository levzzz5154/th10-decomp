// 0x004379E0..0x004379FE: create a texture from the device global, returning
// the created texture rather than the HRESULT.  The height arrives in ECX and
// the width in EDX.
extern "C" int __stdcall D3DXCreateTexture_004521a0(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture);
extern "C" void* data_00491c30;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void* __fastcall CreateTexture_004379e0(unsigned int height, unsigned int width) {
    void* device = data_00491c30;
    void* texture;
    D3DXCreateTexture_004521a0(device, width, height, 1, 0, 0x19, 1, &texture);
    return texture;
}
#pragma code_seg()
