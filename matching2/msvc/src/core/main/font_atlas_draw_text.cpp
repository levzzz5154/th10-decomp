// 0x00437FE0..0x004381DD: draw one line of text into a texture, unshadowed.
//
// The sibling of 0x00437DB0. The atlas is first filled with the text colour
// (so that anti-aliased edges blend towards it), the string is drawn once at
// twice the requested x, the drawn rows are converted, and the touched
// rectangle is copied to the texture's top surface at the destination.
#include "th10/runtime/core/main/font_atlas_draw_text.hpp"
#include <string.h>

// Copy a rectangle of the atlas to the top surface of a texture.
static __forceinline void CopyAtlasToTexture(FontTexture_00437fe0* texture, const FontAtlasRect_00437fe0* destination,
                                             const FontAtlasRect_00437fe0* source) {
    FontSurface_00437fe0* surface;
    texture->methods->GetSurfaceLevel(texture, 0, &surface);
    D3DXLoadSurfaceFromMemory_004521a6(surface, 0, destination, g_font_atlas_surface.pixels, g_font_atlas_surface.format,
                                       g_font_atlas_surface.pitch, 0, source, 4, 0);
    if (surface != 0)
        surface->methods->Release(surface);
}

#pragma code_seg(".text$02text")
void __stdcall FontAtlas_DrawPlainText_00437fe0(const FontAtlasRect_00437fe0* destination, int x, int size,
                                                unsigned int color, const char* text,
                                                FontTexture_00437fe0* texture) {
    void* font;
    if (size <= 17)
        font = g_font_height_32;
    else if (size <= 18)
        font = g_font_height_34;
    else if (size <= 19)
        font = g_font_height_36;
    else if (size <= 20)
        font = g_font_height_38;
    else if (size <= 21)
        font = g_font_height_40;
    else if (size <= 22)
        font = g_font_height_42;
    else if (size <= 23)
        font = g_font_height_44;
    else if (size <= 24)
        font = g_font_height_46;
    else if (size <= 25)
        font = g_font_height_48;
    else if (size <= 26)
        font = g_font_height_50;
    else if (size <= 27)
        font = g_font_height_52;
    else if (size <= 28)
        font = g_font_height_54;
    else if (size <= 29)
        font = g_font_height_56;
    else if (size <= 30)
        font = g_font_height_58;
    else
        font = g_font_height_60;
    if (size < 17)
        size = 17;

    g_font_atlas_surface.Fill(color);
    void* dc = g_font_atlas_surface.dc;
    void* previous = SelectObject(dc, font);
    int row_count = size * 2 + 6;
    g_font_atlas_surface.InvertAlpha(row_count);
    SetBkMode(dc, 1);
    int length = strlen(text);
    SetTextColor(dc, color);
    TextOutA(dc, x * 2, 0, text, length);
    SelectObject(dc, previous);
    g_font_atlas_surface.InvertAlpha(row_count);
    FontAtlas_Convert_00436da0(&g_font_atlas_surface, row_count);
    SelectObject(dc, previous);

    FontAtlasRect_00437fe0 source;
    source.left = 0;
    source.top = 0;
    source.right = (destination->right - destination->left) * 2 + 22;
    source.bottom = size * 2 + 2;
    if (source.right > 1024)
        source.right = 1024;

    CopyAtlasToTexture(texture, destination, &source);
}
#pragma code_seg()

#include "resource_file.cpp"
