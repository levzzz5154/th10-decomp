// Compiler context only. Its caller and loader metadata are not game code.
#pragma code_seg(".text$09tidy")
#include "../../src/render/gdi_font_state.cpp"
#include "th10/render/gdi_surface.hpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall GdiFontStateCompilerContext(GdiSurface* surface, const char* text,
                                                     const int* values) {
    return surface->DrawTextSized(text, values[0], values[1], values[2], values[3], values[4]);
}
#pragma code_seg()

// LINK 7.10 requires this loader record for an /EHsc native image. The image
// is a compiler artifact with /SAFESEH:NO; none of this data is exported.
#pragma section(".rdata$00config", read)
extern "C" __declspec(allocate(".rdata$00config"))
const unsigned int _load_config_used[18] = {72};
