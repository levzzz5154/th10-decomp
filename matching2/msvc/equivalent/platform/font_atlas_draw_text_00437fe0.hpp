#ifndef TH10_PLATFORM_FONT_ATLAS_DRAW_TEXT_00437FE0_HPP
#define TH10_PLATFORM_FONT_ATLAS_DRAW_TEXT_00437FE0_HPP
#include <stddef.h>

struct Surface_00436ca0;
// 0x00436CA0: fill the 16-bit surface with one colour.
__declspec(noinline) void __stdcall FillRgb444_00436ca0(Surface_00436ca0* surface, unsigned int color);

struct FontAtlasRect_00437fe0 {
    int left;
    int top;
    int right;
    int bottom;
};

// The software font atlas at 0x00474CB0: palette, pixel buffer and the device
// context the fonts are drawn through.
struct FontAtlas_00437fe0 {
    unsigned char palette[0x100];
    unsigned int format;                // +0x100
    unsigned char reserved_104[8];
    int byte_size;                      // +0x10C
    unsigned int pitch;                 // +0x110
    void* dc;                           // +0x114
    unsigned char reserved_118[8];
    void* pixels;                       // +0x120

    void Fill(unsigned int color) {
        FillRgb444_00436ca0(reinterpret_cast<Surface_00436ca0*>(this), color);
    }
    // 0x00437160: flip the alpha of the first rows.
    char InvertAlpha(int row_count);
};
typedef char FontAtlasDc_00437fe0[offsetof(FontAtlas_00437fe0, dc) == 0x114 ? 1 : -1];
typedef char FontAtlasPixels_00437fe0[offsetof(FontAtlas_00437fe0, pixels) == 0x120 ? 1 : -1];

struct FontSurface_00437fe0;
struct FontSurfaceMethods_00437fe0 {
    void* query_interface;
    void* add_ref;
    unsigned long (__stdcall* Release)(FontSurface_00437fe0*);
};
struct FontSurface_00437fe0 {
    FontSurfaceMethods_00437fe0* methods;
};

struct FontTexture_00437fe0;
struct FontTextureMethods_00437fe0 {
    void* reserved_00[0x48 / 4];
    long (__stdcall* GetSurfaceLevel)(FontTexture_00437fe0*, unsigned int level, FontSurface_00437fe0** surface);
};
struct FontTexture_00437fe0 {
    FontTextureMethods_00437fe0* methods;
};

extern "C" {
extern FontAtlas_00437fe0 data_00474cb0;
// The fifteen fonts, one object each, largest first: data_00491868 is used
// above 30 pixels, data_0049186c up to 30, ... data_004918a0 up to 17.
// They are separate globals: read as elements of one array, the font no longer
// competes for a register in the size ladder and the size loses its own.
extern void* data_00491868;
extern void* data_0049186c;
extern void* data_00491870;
extern void* data_00491874;
extern void* data_00491878;
extern void* data_0049187c;
extern void* data_00491880;
extern void* data_00491884;
extern void* data_00491888;
extern void* data_0049188c;
extern void* data_00491890;
extern void* data_00491894;
extern void* data_00491898;
extern void* data_0049189c;
extern void* data_004918a0;

__declspec(dllimport) void* __stdcall SelectObject(void* dc, void* object);
__declspec(dllimport) int __stdcall SetBkMode(void* dc, int mode);
__declspec(dllimport) unsigned int __stdcall SetTextColor(void* dc, unsigned int color);
__declspec(dllimport) int __stdcall TextOutA(void* dc, int x, int y, const char* text, int count);

// 0x00436DA0: turn the drawn rows into the atlas format.
void __stdcall FontAtlas_Convert_00436da0(FontAtlas_00437fe0* atlas, int row_count);
long __stdcall D3DXLoadSurfaceFromMemory_004521a6(FontSurface_00437fe0* surface, const void* palette,
                                                  const FontAtlasRect_00437fe0* destination, const void* memory,
                                                  unsigned int format, unsigned int pitch,
                                                  const void* source_palette, const FontAtlasRect_00437fe0* source,
                                                  unsigned int filter, unsigned int color_key);
}

// 0x00437FE0: draw one line of text, without the shadow, into a texture.
void __stdcall FontAtlas_DrawPlainText_00437fe0(const FontAtlasRect_00437fe0* destination, int x, int size,
                                                unsigned int color, const char* text, FontTexture_00437fe0* texture);

#endif
