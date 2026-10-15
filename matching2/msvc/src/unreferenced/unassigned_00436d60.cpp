// 0x00436D60: add one ARGB4444 texel's colour channels to running sums
// when the texel is not fully transparent.
struct ColorSums_00436d60 {
    int red, green, blue;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall AccumulateArgb4444_00436d60(ColorSums_00436d60* sums, const unsigned short* texel, int* count) {
    if (*texel & 0xF000) {
        sums->red += (*texel >> 8) & 0xF;
        sums->green += (*texel >> 4) & 0xF;
        sums->blue += *texel & 0xF;
        ++*count;
    }
}
#pragma code_seg()
