// Experiment TU: MarkText body in isolation for receiver-register study.
#include <string.h>
#include <stdarg.h>
#include "th10/game/ending_script_cluster/script_executor_text_anchors.hpp"

extern "C" int __cdecl recovery_vsprintf(
    char* buffer, const char* format, char* args);
void __stdcall SpriteText_Dispatch(
    AnmTextResource* resource, int font_height,
    const char* text, void* texture, int horizontal_offset,
    unsigned int color, int unshadowed);

#pragma code_seg(".text$00447a50_fn")
void AnmTextVm::MarkText(
    void* manager, unsigned int color, const char* format) {
    char buffer[128];
    recovery_vsprintf(buffer, format, const_cast<char*>(format));
    AnmTextResource* text_resource = resource;
    SpriteText_Dispatch(
        text_resource, static_cast<int>(font_height), buffer,
        text_resource->texture, 0, color, (flags_360 >> 1) & 1);
    flags_35c |= 1;
}
#pragma code_seg()
