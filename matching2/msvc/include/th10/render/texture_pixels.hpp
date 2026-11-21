#pragma once

// D3D9 formats used by the font DIB and the ANM surface. MSVC/i386 lays out
// these 16-bit fields from the least significant bit, blue first.
namespace TexturePixels {
    enum Format { A8R8G8B8 = 21, A1R5G5B5 = 25, A4R4G4B4 = 26 };

    struct Argb8888 { unsigned char b, g, r, a; };
    struct Argb1555 { unsigned short b : 5, g : 5, r : 5, a : 1; };
    struct Argb4444 { unsigned short b : 4, g : 4, r : 4, a : 4; };

    static inline void AddOpaque8888(unsigned int* rgb, unsigned int* count, const Argb8888* pixel) {
        if (pixel->a != 0) {
            rgb[0] += pixel->r;
            rgb[1] += pixel->g;
            rgb[2] += pixel->b;
            ++*count;
        }
    }
}
