// 0x00447050..0x00447078: AnimationTexture_Create
// Native MSVC 13.10 LTCG supplies the private EDX/ECX/EDI/ESI ABI through
// layout/ltcg/d3703_animation_texture_00447050.json.
extern "C" int data_0046f288[];
extern "C" int data_0046f2a0[];
extern "C" void* data_00491c30;
extern "C" int __stdcall asm_D3DXCreateTexture_004521a0(
        void*, unsigned int, unsigned int, unsigned int, unsigned int,
        unsigned int, unsigned int, void**);

#ifndef ANIMATION_TEXTURE_CREATE_SECTION
#define ANIMATION_TEXTURE_CREATE_SECTION ".text$01anim"
#endif
#pragma code_seg(ANIMATION_TEXTURE_CREATE_SECTION)
__declspec(noinline) int AnimationTextureCreate_00447050(
        int width, int height, void* output, int format_index) {
    int format = data_0046f288[format_index];
    asm_D3DXCreateTexture_004521a0(data_00491c30, width, height, 1, 0, format, 1,
                                   (void**)output);
    *(int*)((unsigned char*)output + 0xc) = data_0046f2a0[format_index];
    return 0;
}
#pragma code_seg()
