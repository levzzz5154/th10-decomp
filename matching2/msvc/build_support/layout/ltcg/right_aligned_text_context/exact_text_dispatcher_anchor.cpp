// Complete text dispatcher and VM formatter.
// The genuine full caller graph lets native LTCG choose their private ABI.

#include <stdarg.h>
#include "../../../include/contexts/game/right_aligned_text_context/recovery_mark_text_and_dispatcher_004479d0.hpp"

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
void __stdcall RecoveryDispatchText_004479d0(
    RecoveryTextResource* resource, void* texture,
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

#pragma code_seg(".text$00447a50_fn")
void __cdecl RecoveryTextVm::MarkText(
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
    RecoveryTextResource* text_resource = resource;
    RecoveryDispatchText_004479d0(
        text_resource, text_resource->texture, 0, height, color, buffer,
        (flags_360 >> 1) & 1);
    flags_35c |= 1;
}
#pragma code_seg()
