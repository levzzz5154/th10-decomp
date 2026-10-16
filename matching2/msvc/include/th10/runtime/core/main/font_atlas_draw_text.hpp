#ifndef TH10_PLATFORM_FONT_ATLAS_DRAW_TEXT_00437FE0_HPP
#define TH10_PLATFORM_FONT_ATLAS_DRAW_TEXT_00437FE0_HPP
#include <stddef.h>

struct Surface;
// 0x00436CA0: fill the 16-bit surface with one colour.
__declspec(noinline) void __stdcall FillRgb444(Surface* surface, unsigned int color);

struct FontAtlasRect {
    int left;
    int top;
    int right;
    int bottom;
};

// The software font atlas at 0x00474CB0: palette, pixel buffer and the device
// context the fonts are drawn through.
struct FontAtlas3 {
    unsigned char palette[0x100];
    unsigned int format;                // +0x100
    unsigned char reserved_104[8];
    int byte_size;                      // +0x10C
    unsigned int pitch;                 // +0x110
    void* dc;                           // +0x114
    unsigned char reserved_118[8];
    void* pixels;                       // +0x120

    void Fill(unsigned int color) {
        FillRgb444(reinterpret_cast<Surface*>(this), color);
    }
    // 0x00437160: flip the alpha of the first rows.
    char InvertAlpha(int row_count);
};
typedef char FontAtlasDc[offsetof(FontAtlas3, dc) == 0x114 ? 1 : -1];
typedef char FontAtlasPixels[offsetof(FontAtlas3, pixels) == 0x120 ? 1 : -1];

struct FontSurface2;
struct FontSurfaceMethods2 {
    void* query_interface;
    void* add_ref;
    unsigned long (__stdcall* Release)(FontSurface2*);
};
struct FontSurface2 {
    FontSurfaceMethods2* methods;
};

struct FontTexture;
struct FontTextureMethods {
    void* reserved_00[0x48 / 4];
    long (__stdcall* GetSurfaceLevel)(FontTexture*, unsigned int level, FontSurface2** surface);
};
struct FontTexture {
    FontTextureMethods* methods;
};

extern "C" {
extern FontAtlas3 g_font_atlas_surface;
// The fifteen fonts, one GDI object each: g_font_height_60 is used above 30
// pixels, g_font_height_58 up to 30, ... g_font_height_32 up to 17. The name
// is the font's own pixel height; the size ladder picks roughly twice it.
// They are separate globals: read as elements of one array, the font no longer
// competes for a register in the size ladder and the size loses its own.
extern void* g_font_height_60;
extern void* g_font_height_58;
extern void* g_font_height_56;
extern void* g_font_height_54;
extern void* g_font_height_52;
extern void* g_font_height_50;
extern void* g_font_height_48;
extern void* g_font_height_46;
extern void* g_font_height_44;
extern void* g_font_height_42;
extern void* g_font_height_40;
extern void* g_font_height_38;
extern void* g_font_height_36;
extern void* g_font_height_34;
extern void* g_font_height_32;

__declspec(dllimport) void* __stdcall SelectObject(void* dc, void* object);
__declspec(dllimport) int __stdcall SetBkMode(void* dc, int mode);
__declspec(dllimport) unsigned int __stdcall SetTextColor(void* dc, unsigned int color);
__declspec(dllimport) int __stdcall TextOutA(void* dc, int x, int y, const char* text, int count);

// 0x00436DA0: turn the drawn rows into the atlas format.
void __stdcall FontAtlas_Convert(FontAtlas3* atlas, int row_count);
long __stdcall D3DXLoadSurfaceFromMemory(FontSurface2* surface, const void* palette,
                                                  const FontAtlasRect* destination, const void* memory,
                                                  unsigned int format, unsigned int pitch,
                                                  const void* source_palette, const FontAtlasRect* source,
                                                  unsigned int filter, unsigned int color_key);
}

// 0x00437FE0: draw one line of text, without the shadow, into a texture.
void __stdcall FontAtlas_DrawPlainText(const FontAtlasRect* destination, int x, int size,
                                                unsigned int color, const char* text, FontTexture* texture);

#endif
