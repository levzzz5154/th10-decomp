// The text writer at 0x00447A50 as the executor's else branch calls it: the
// text object is an explicit second parameter. Right-to-left evaluation then
// pushes the text and color, calls the handle validation, and loads the
// manager last, as retail does. The va_list comes from the manager's address,
// so the object never has its address taken and LTCG passes it in ESI like
// the member's receiver. Same body as RecoveryTextVm::MarkText.
#include <stdarg.h>
#include "th10/game/recovery_mark_text_and_dispatcher.hpp"
extern "C" int __cdecl recovery_vsprintf(char* buffer, const char* format, char* args);
#pragma code_seg(".text$00447a50_standin")
__declspec(noinline) void __cdecl RecoveryMarkText(void* manager, RecoveryTextVm* vm, ...) {
    char buffer[128];
    const unsigned int height = vm->font_height;
    va_list args = reinterpret_cast<va_list>(&manager) + 2 * sizeof(void*);
    va_list color_home = args;
    (void)va_arg(args, unsigned int);
    const char* format = va_arg(args, const char*);
    recovery_vsprintf(buffer, format, args);
    const unsigned int color = va_arg(color_home, unsigned int);
    RecoveryTextResource* text_resource = vm->resource;
    RecoveryDispatchText2(
        text_resource, text_resource->texture, 0, height, color, buffer,
        (vm->flags_360 >> 1) & 1);
    vm->flags_35c |= 1;
}
#pragma code_seg()
