#pragma once

// An off-screen GDI drawing surface: a memory DC with a DIB section selected
// into it, used to render text that is then copied into a texture.
struct GdiSurface {
    unsigned char unknown_000[0x100];
    int font_index;                 // +0x100
    int width;                      // +0x104
    int height;                     // +0x108
    unsigned char unknown_10c[8];
    void* dc;                       // +0x114
    void* previous_bitmap;          // +0x118
    void* bitmap;                   // +0x11C
    void* pixels;                   // +0x120

    // Draws `text` with its top-left corner one pixel right of and below
    // (x, y). Unless `shadow` is -1 the text is first drawn in that colour
    // around the final position to give it an outline.
    bool DrawText(const char* text, int x, int y, void* font,
                  unsigned long color, unsigned long shadow);

    // The same with a font of the default face, `size` pixels high, made for
    // this one call.
    bool DrawTextSized(const char* text, int x, int y, int size,
                       unsigned long color, unsigned long shadow);
};
