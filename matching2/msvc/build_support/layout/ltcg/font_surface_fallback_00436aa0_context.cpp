// Compiler context only; never selected as recovered game code.
// Retail keeps an out-of-line copy of the fallback create although its one
// call is inlined. The release and create bodies are compiled alongside as
// ABI anchors, and the caller below - built with inlining off - gives the
// pass a call to derive the register arguments from.
#include "th10/platform/native_font_start.hpp"
#include "native_font_start/release_surface.cpp"
#include "../../../src/core/main/font_surface_create.cpp"
#include "../../../src/core/main/font_surface_create_fallback.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$a09context")
extern "C" int __stdcall FontSurfaceFallbackContext(GdiSurface2** surfaces,const int* sizes,int count) {
    int created=0;
    for (int index=0;index<count;++index)
        created+=FontSurface_CreateWithFallback2(surfaces[index],sizes[0],sizes[1],sizes[2]+index);
    return created;
}
#pragma code_seg()
#pragma inline_depth()
