typedef long (__stdcall* D3DXCreateTextureFn_004521a0)(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture);
extern "C" D3DXCreateTextureFn_004521a0 imp_D3DXCreateTexture;

// 0x004521A0..0x004521A5: imported D3DXCreateTexture tail thunk.
extern "C" long __stdcall Th10_D3DXCreateTexture(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture) {
    return imp_D3DXCreateTexture(device, width, height, mip_levels, usage, format, pool, texture);
}
