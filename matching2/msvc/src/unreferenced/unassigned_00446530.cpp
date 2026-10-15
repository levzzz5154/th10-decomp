// 0x00446530: add one ARGB1555 texel's colour channels to running sums
// when its alpha bit is set.
struct ColorSums_00446530 {
    int red, green, blue;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall AccumulateArgb1555_00446530(ColorSums_00446530* sums, const unsigned short* texel, int* count) {
    if (*texel & 0x8000) {
        sums->red += (*texel >> 10) & 0x1F;
        sums->green += (*texel >> 5) & 0x1F;
        sums->blue += *texel & 0x1F;
        ++*count;
    }
}
#pragma code_seg()
