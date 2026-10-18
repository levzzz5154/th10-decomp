// Compiler context only; never selected as recovered game code. Retail reaches
// the plain-text draw by direct call from the atlas draw, so this caller gives
// the whole-program link that same direct-call edge (the link-entrance form
// compiles the body's stack parameters differently).
#include "../../../src/core/main/font_atlas_draw_text.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall FontAtlasDrawTextContext(FontAtlasRect* destination, int x, int size,
                                                                      unsigned int color, const char* text,
                                                                      FontTexture* texture) {
    FontAtlas_DrawPlainText(destination, x, size, color, text, texture);
    return x;
}
#pragma code_seg()
