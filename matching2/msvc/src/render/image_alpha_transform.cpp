#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// Ghidra observes a surface receiver in ECX, row_count at [ESP+4], and a
// byte-sized success result in AL. Only the accessed fields are laid out here.
struct ImageSurface_00437160 {
    unsigned char pad_000[0x100];
    int format;                       // +0x100
    unsigned char pad_104[0x0C];
    int pitch;                        // +0x110
    unsigned char pad_114[0x0C];
    unsigned char* pixels;            // +0x120

    __declspec(noinline) char InvertAlpha(int row_count);
};

// 0x00437160: modify the alpha representation for the selected pixel format.
__declspec(noinline) char ImageSurface_00437160::InvertAlpha(int row_count) {
    int byte_count = pitch * row_count;
    unsigned char* bytes = pixels;

    switch (format) {
    case 0x1A:
        // Transform the high nibble at byte offsets 1, 3, 5, and so on.
        for (int index = 1; index < byte_count; index += 2) {
            bytes[index] ^= 0xF0;
        }
        return 1;

    case 0x19:
        // 16-bit pixels: toggle the high alpha bit; clear the pixel when its
        // previous alpha bit was set.
        if (byte_count <= 0) {
            return 1;
        }
        {
            unsigned short* words = (unsigned short*)bytes;
            unsigned int count = ((unsigned int)byte_count - 1) / 2 + 1;
            do {
                unsigned short value = *words;
                unsigned int result = ((~value ^ value) & 0x7FFF) ^ ~value;
                *words = (unsigned short)result;
                if (!(result & 0x8000)) {
                    result &= 0x8000;
                    *words = (unsigned short)result;
                }
                ++words;
            } while (--count);
        }
        return 1;

    case 0x15:
        // Four-byte pixels: invert the fourth byte in each pixel.
        for (int index = 3; index < byte_count; index += 4) {
            bytes[index] = ~bytes[index];
        }
        return 1;

    default:
        return 0;
    }
}
