// 0x00447BB0: format text and draw it centred on an animation's text surface.
//
// The text is centred on half the surface width; a character is taken to be
// half the font height wide. Native LTCG passes the animation in ESI, leaving
// the unused manager, the colour, the format and its arguments on the stack.

#include <stdarg.h>
#include <string.h>
#include "../../../build_support/include/contexts/game/right_aligned_text_context/recovery_script_executor_text_sibling_anchors.hpp"

extern "C" int __cdecl recovery_vsprintf(
    char* buffer, const char* format, char* args);

#pragma code_seg(".text$00447bb0_fn")
void __cdecl HintVm::FormatCentered(
    void* manager, ...) {
    char buffer[128];
    const unsigned char font = font_height;
    unsigned int height = 17;
    if (font > 0)
        height = font;
    va_list args;
    va_start(args, manager);
    va_list color_home = args;
    (void)va_arg(args, unsigned int);
    const char* format = va_arg(args, const char*);
    recovery_vsprintf(buffer, format, args);
    va_end(args);
    const unsigned int color = va_arg(color_home, unsigned int);
    va_end(color_home);

    const unsigned int length = static_cast<unsigned int>(strlen(buffer));
    RecoveryTextResource* text_resource = resource;
    const unsigned int mode = (mode_flags >> 1) & 1;
    const unsigned int quarter_width = ((height - 1u) * length) >> 2;
    const float resource_width =
        text_resource->width;
    // Retail first truncates the resource width to an integer, then divides
    // that signed integer by two toward zero. Its final subtraction preserves
    // the low 32 bits of the unsigned text-span product.
    const int half_width = static_cast<int>(resource_width) / 2;
    const int horizontal_offset = static_cast<int>(
        static_cast<unsigned int>(half_width) - quarter_width);
    RecoveryDispatchText_004479d0(
        text_resource, text_resource->texture, horizontal_offset,
        static_cast<int>(height), color, buffer, mode);
    flags |= 1;
}
#pragma code_seg()
