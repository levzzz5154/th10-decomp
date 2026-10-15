// D3DFMT_A1R5G5B5: the high bit is alpha; the lower 15 bits hold color.
struct Pixel1555 {
    unsigned short colors : 15;
    unsigned short alpha : 1;
};

// Ghidra observes a surface receiver in ECX, row_count at [ESP+4], and a
// byte-sized success result in AL. Only the accessed fields are laid out here.
struct ImageSurface {
    unsigned char pad_000[0x100];
    int format;                       // +0x100
    unsigned char pad_104[0x0C];
    int pitch;                        // +0x110
    unsigned char pad_114[0x0C];
    unsigned char* pixels;            // +0x120

    __declspec(noinline) char InvertAlpha(int row_count);
};

// 0x00437160: modify the alpha representation for the selected pixel format.
#pragma code_seg(".text$01accessor")
__declspec(noinline) char ImageSurface::InvertAlpha(int row_count) {
    int byte_count = pitch * row_count;
    unsigned char* bytes = pixels;

    switch (format) {
    case 0x1A:
        // Transform the high nibble at byte offsets 1, 3, 5, and so on.
        for (int index = 1; index < byte_count; index += 2) {
            bytes[index] ^= 0xF0;
        }
        break;

    case 0x19:
        // 16-bit pixels: toggle the high alpha bit; clear the pixel when its
        // previous alpha bit was set.
        if (byte_count <= 0) {
            break;
        }
        {
            for (int index = 0; index < byte_count; index += 2, bytes += 2) {
                ((Pixel1555*)bytes)->alpha = !((Pixel1555*)bytes)->alpha;
                if (!((Pixel1555*)bytes)->alpha) {
                    ((Pixel1555*)bytes)->colors = 0;
                }
            }
        }
        break;

    case 0x15:
        // Four-byte pixels: invert the fourth byte in each pixel.
        for (int index = 3; index < byte_count; index += 4) {
            bytes[index] = ~bytes[index];
        }
        break;

    default:
        return 0;
    }
    return 1;
}

#pragma code_seg()
