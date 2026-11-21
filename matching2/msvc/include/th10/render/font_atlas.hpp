#pragma once

#include <stddef.h>

struct Surface;
__declspec(noinline) void __stdcall FillRgb444(Surface* surface, unsigned int color);

// Software DIB used by both the plain and outlined GDI text paths.
struct FontAtlas {
    unsigned char palette[0x100];
    int format;
    int width;
    int height;
    int byte_size;
    int pitch;                     // Bytes between source rows.
    void* dc;
    unsigned char reserved_118[8];
    unsigned char* pixels;

    void Fill(unsigned int color) {
        FillRgb444(reinterpret_cast<Surface*>(this), color);
    }
    char InvertAlpha(int row_count);
};

typedef char FontAtlasDc[offsetof(FontAtlas, dc) == 0x114 ? 1 : -1];
typedef char FontAtlasPixels[offsetof(FontAtlas, pixels) == 0x120 ? 1 : -1];

extern "C" FontAtlas g_font_atlas_surface;
char __stdcall FontAtlas_FillTransparentPixels(FontAtlas* atlas, unsigned int rows);
