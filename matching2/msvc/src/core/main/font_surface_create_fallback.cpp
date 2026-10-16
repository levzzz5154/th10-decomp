// 0x00436AA0: create a font surface, falling back to a 32-bit format when the
// requested 16-bit one is refused.
//
// The 1555 and 4444 formats fall back to A8R8G8B8 and 565 to X8R8G8B8. The
// font cache initialiser has the only call, inlined; retail keeps this
// out-of-line copy with the surface in EBX, the width in EDI and the height
// in ESI.
#include "th10/platform/native_font_start.hpp"
#pragma code_seg(".text$a05m_fallback")
bool __stdcall FontSurface_CreateWithFallback2(GdiSurface2* surface,int width,int height,int format) {
    if (FontSurface_Create(surface,width,height,format))
        return true;
    if (format==0x19 || format==0x1a)
        return FontSurface_Create(surface,width,height,0x15);
    if (format==0x17)
        return FontSurface_Create(surface,width,height,0x16);
    return false;
}
#pragma code_seg()
