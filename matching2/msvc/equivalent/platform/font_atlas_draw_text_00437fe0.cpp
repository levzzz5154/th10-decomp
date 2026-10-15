// 0x00437FE0..0x004381DD: draw one line of text into a texture, unshadowed.
//
// The sibling of 0x00437DB0. The atlas is first filled with the text colour
// (so that anti-aliased edges blend towards it), the string is drawn once at
// twice the requested x, the drawn rows are converted, and the touched
// rectangle is copied to the texture's top surface at the destination.
#include "font_atlas_draw_text_00437fe0.hpp"
#include <string.h>

// Copy a rectangle of the atlas to the top surface of a texture.
static __forceinline void CopyAtlasToTexture(FontTexture_00437fe0* texture, const FontAtlasRect_00437fe0* destination,
                                             const FontAtlasRect_00437fe0* source) {
    FontSurface_00437fe0* surface;
    texture->methods->GetSurfaceLevel(texture, 0, &surface);
    D3DXLoadSurfaceFromMemory_004521a6(surface, 0, destination, data_00474cb0.pixels, data_00474cb0.format,
                                       data_00474cb0.pitch, 0, source, 4, 0);
    if (surface != 0)
        surface->methods->Release(surface);
}

#pragma code_seg(".text$02text")
void __stdcall FontAtlas_DrawPlainText_00437fe0(const FontAtlasRect_00437fe0* destination, int x, int size,
                                                unsigned int color, const char* text,
                                                FontTexture_00437fe0* texture) {
    void* font;
    if (size <= 17)
        font = data_004918a0;
    else if (size <= 18)
        font = data_0049189c;
    else if (size <= 19)
        font = data_00491898;
    else if (size <= 20)
        font = data_00491894;
    else if (size <= 21)
        font = data_00491890;
    else if (size <= 22)
        font = data_0049188c;
    else if (size <= 23)
        font = data_00491888;
    else if (size <= 24)
        font = data_00491884;
    else if (size <= 25)
        font = data_00491880;
    else if (size <= 26)
        font = data_0049187c;
    else if (size <= 27)
        font = data_00491878;
    else if (size <= 28)
        font = data_00491874;
    else if (size <= 29)
        font = data_00491870;
    else if (size <= 30)
        font = data_0049186c;
    else
        font = data_00491868;
    if (size < 17)
        size = 17;

    data_00474cb0.Fill(color);
    void* dc = data_00474cb0.dc;
    void* previous = SelectObject(dc, font);
    int row_count = size * 2 + 6;
    data_00474cb0.InvertAlpha(row_count);
    SetBkMode(dc, 1);
    int length = strlen(text);
    SetTextColor(dc, color);
    TextOutA(dc, x * 2, 0, text, length);
    SelectObject(dc, previous);
    data_00474cb0.InvertAlpha(row_count);
    FontAtlas_Convert_00436da0(&data_00474cb0, row_count);
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

#include "../../src/core/main/resource_file.cpp"
