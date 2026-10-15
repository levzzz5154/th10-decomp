#include "../build_support/include/asm_encoding.hpp"

typedef long (__stdcall* D3DXCreateTextureFn_004521a0)(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture);
extern "C" D3DXCreateTextureFn_004521a0 data_004662e4;

// 0x004521A0..0x004521A5: imported D3DXCreateTexture tail thunk.
extern "C" long __stdcall asm_D3DXCreateTexture_004521a0(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture) {
    return data_004662e4(device, width, height, mip_levels, usage, format, pool, texture);
}
