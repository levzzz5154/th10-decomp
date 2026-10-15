// Genuine, complete helper models for the 0040BD80 caller cluster.
// The native MSVC LTCG build determines the helpers' private register inputs.

#include <stdarg.h>
#include "th10/game/recovery_script_executor_text_anchors.hpp"

extern "C" {
extern unsigned char recovery_decoded_path_00497d40[];
int __cdecl recovery_vsprintf(
    char* buffer, const char* format, char* args);

// These image text-rasterization entries use six ordinary stack arguments
// and RET 24. Their bodies contain the GDI/texture upload effects; neither
// call is replaced with a placeholder or a guessed register-only prototype.
void __stdcall recovery_draw_shadowed(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
void __stdcall recovery_draw_unshadowed(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
}

#pragma code_seg(".text$00417010_fn")
char* __stdcall RecoveryDecodePath(const unsigned char* encoded) {
    unsigned char* output = recovery_decoded_path_00497d40;
    unsigned char key = 0x77;
    unsigned char increment = 7;
    unsigned char decoded;
    do {
        decoded = *encoded ^ key;
        *output = decoded;
        ++output;
        key += increment;
        ++encoded;
        increment += 0x10;
    } while (decoded != 0);
    return reinterpret_cast<char*>(recovery_decoded_path_00497d40);
}
#pragma code_seg()

#pragma code_seg(".text$004479d0_fn")
void __stdcall RecoveryDispatchText_004479d0(
    RecoveryTextResource* resource, int font_height,
    const char* text, void* texture, int horizontal_offset,
    unsigned int color, int unshadowed) {
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
        text_resource, height, buffer, text_resource->texture, 0, color,
        (flags_360 >> 1) & 1);
    flags_35c |= 1;
}
#pragma code_seg()
