// 0x00436CA0: fill a 16-bit surface with one colour converted from X8R8G8B8 to X4R4G4B4.
struct Surface_00436ca0 {
    unsigned char unknown0000[0x10C];
    int byte_size;
    unsigned char unknown0110[0x10];
    unsigned short* pixels;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall FillRgb444_00436ca0(Surface_00436ca0* surface, unsigned int color) {
    unsigned short packed = (unsigned short)(((((color >> 20) & 0xF) << 4 | ((color >> 12) & 0xF)) << 4) | ((color >> 4) & 0xF));
    unsigned short* pixel;
    int i;
    for (i = 0, pixel = surface->pixels; i < surface->byte_size; i += 2, ++pixel) *pixel = packed;
}
#pragma code_seg()
