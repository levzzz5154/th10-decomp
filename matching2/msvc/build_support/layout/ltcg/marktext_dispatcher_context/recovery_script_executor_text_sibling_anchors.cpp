// Genuine complete models of the right-aligned and centered VM formatters.
// The caller cluster and real DispatchText body determine their private ABI.

#include <stdarg.h>
#include <string.h>
#include "../../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_text_sibling_anchors.hpp"

extern "C" int __cdecl recovery_vsprintf_004524a6(
    char* buffer, const char* format, char* args);

#pragma code_seg(".text$00447ae0_fn")
void __cdecl HintVm::FormatRightAligned(
    void* manager, ...) {
    char buffer[128];
    unsigned int height = font_height;
    if (height == 0)
        height = 17;
    va_list args;
    va_start(args, manager);
    va_list color_home = args;
    (void)va_arg(args, unsigned int);
    const char* format = va_arg(args, const char*);
    recovery_vsprintf_004524a6(buffer, format, args);
    va_end(args);
    const unsigned int color = va_arg(color_home, unsigned int);
    va_end(color_home);

    const unsigned int length = static_cast<unsigned int>(strlen(buffer));
    RecoveryTextResource_004479d0* text_resource = resource;
    const unsigned int mode = (mode_flags >> 1) & 1;
    const unsigned int text_width = ((height - 1u) * length) >> 1;
    // Keep the unsigned width conversion: retail emits FILD plus a possible
    // 2^32 correction before subtracting it from the resource's float width.
    const float resource_width =
        reinterpret_cast<RecoveryTextResourceWidthView_00447ae0*>(text_resource)->width;
    const int horizontal_offset = static_cast<int>(resource_width - text_width);
    RecoveryDispatchText_004479d0(
        text_resource, text_resource->texture, horizontal_offset,
        static_cast<int>(height), color, buffer, mode);
    flags |= 1;
}
#pragma code_seg()

#pragma code_seg(".text$00447bb0_fn")
void __cdecl HintVm::FormatCentered(
    void* manager, ...) {
    char buffer[128];
    unsigned int height = font_height;
    if (height == 0)
        height = 17;
    va_list args;
    va_start(args, manager);
    va_list color_home = args;
    (void)va_arg(args, unsigned int);
    const char* format = va_arg(args, const char*);
    recovery_vsprintf_004524a6(buffer, format, args);
    va_end(args);
    const unsigned int color = va_arg(color_home, unsigned int);
    va_end(color_home);

    const unsigned int length = static_cast<unsigned int>(strlen(buffer));
    RecoveryTextResource_004479d0* text_resource = resource;
    const unsigned int mode = (mode_flags >> 1) & 1;
    const unsigned int quarter_width = ((height - 1u) * length) >> 2;
    const float resource_width =
        reinterpret_cast<RecoveryTextResourceWidthView_00447ae0*>(text_resource)->width;
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
