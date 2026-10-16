// 0x00446570: add one ARGB4444 texel's colour channels to running sums
// when the texel is not fully transparent.
struct ColorSums3 {
    int red, green, blue;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall AccumulateArgb44442(ColorSums3* sums, const unsigned short* texel, int* count) {
    if (*texel & 0xF000) {
        sums->red += (*texel >> 8) & 0xF;
        sums->green += (*texel >> 4) & 0xF;
        sums->blue += *texel & 0xF;
        ++*count;
    }
}
#pragma code_seg()
