// Compiler context only. Its caller and loader metadata are not game code.
#include "../../src/render/gdi_font_state.cpp"
#include <new>

#pragma code_seg(".text$03context")
extern "C" GdiFontState* __stdcall GdiFontStateCompilerContext(GdiFontState* storage) {
    return new (storage) GdiFontState;
}
#pragma code_seg()

// LINK 7.10 requires this loader record for an /EHsc native image. The image
// is a compiler artifact with /SAFESEH:NO; none of this data is exported.
#pragma section(".rdata$00config", read)
extern "C" __declspec(allocate(".rdata$00config"))
const unsigned int _load_config_used[18] = {72};
