// Complete text dispatcher and VM formatter.
// The genuine full caller graph lets native LTCG choose their private ABI.

#include <stdarg.h>
#include "th10/render/anm_text_dispatcher.hpp"

extern "C" {
int __cdecl recovery_vsprintf(
    char* buffer, const char* format, char* args);

// Both actual drawing entries take six stack arguments and RET 24.
// They return zero for a null surface or its final COM Release count.
// All three dispatcher callers ignore the result; every draw effect remains.
unsigned int __stdcall recovery_draw_shadowed(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
unsigned int __stdcall recovery_draw_unshadowed(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
}

#pragma code_seg(".text$004479d0_fn")
void __stdcall SpriteText_Dispatch(
    AnmTextResource* resource, void* texture,
    int horizontal_offset, int font_height, unsigned int color,
    const char* text, int unshadowed) {
    if (font_height <= 0)
        font_height = 17;
    else if (font_height <= 8)
        return;

    // Integer casts invoke the image's __ftol2 through the compiler's own
    // x87 ABI. The conversions retain left/top/right/bottom order.
    int bounds[4];
    bounds[0] = static_cast<int>(resource->left);
    bounds[1] = static_cast<int>(resource->top);
    bounds[2] = static_cast<int>(resource->right);
    bounds[3] = static_cast<int>(resource->bottom);
    if (unshadowed == 0)
        recovery_draw_shadowed(
            bounds, horizontal_offset, font_height, color, text, texture);
    else
        recovery_draw_unshadowed(
            bounds, horizontal_offset, font_height, color, text, texture);
}
#pragma code_seg()

// A cluster that places another text writer at 0x00447A50 parks this one
// through TH10_MARK_TEXT_SECTION.
#ifndef TH10_MARK_TEXT_SECTION
#define TH10_MARK_TEXT_SECTION ".text$00447a50_fn"
#endif
#pragma code_seg(TH10_MARK_TEXT_SECTION)
void __cdecl AnmTextVm::MarkText(
    void* manager, ...) {
    char buffer[128];
    const unsigned int height = font_height;
    va_list args;
    va_start(args, manager);
    va_list color_home = args;
    (void)va_arg(args, unsigned int);
    const char* format = va_arg(args, const char*);
    recovery_vsprintf(buffer, format, args);
    va_end(args);
    const unsigned int color = va_arg(color_home, unsigned int);
    va_end(color_home);
    AnmTextResource* text_resource = resource;
    SpriteText_Dispatch(
        text_resource, text_resource->texture, 0, height, color, buffer,
        (flags_360 >> 1) & 1);
    flags_35c |= 1;
}
#pragma code_seg()
