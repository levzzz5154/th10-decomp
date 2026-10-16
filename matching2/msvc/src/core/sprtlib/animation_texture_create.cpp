// 0x00447050..0x00447078: AnimationTexture_Create
// Native MSVC 13.10 LTCG supplies the private EDX/ECX/EDI/ESI ABI through
// build_support/layout/ltcg/d3703_animation_texture.json.
extern "C" int g_texture_formats_a[];
extern "C" int g_texture_formats_b[];
extern "C" void* g_d3d_device;
extern "C" int __stdcall asm_D3DXCreateTexture_004521a0(
        void*, unsigned int, unsigned int, unsigned int, unsigned int,
        unsigned int, unsigned int, void**);

#ifndef ANIMATION_TEXTURE_CREATE_SECTION
#define ANIMATION_TEXTURE_CREATE_SECTION ".text$01anim"
#endif
#pragma code_seg(ANIMATION_TEXTURE_CREATE_SECTION)
__declspec(noinline) int AnimationTextureCreate2(
        int width, int height, void* output, int format_index) {
    int format = g_texture_formats_a[format_index];
    asm_D3DXCreateTexture_004521a0(g_d3d_device, width, height, 1, 0, format, 1,
                                   (void**)output);
    *(int*)((unsigned char*)output + 0xc) = g_texture_formats_b[format_index];
    return 0;
}
#pragma code_seg()
