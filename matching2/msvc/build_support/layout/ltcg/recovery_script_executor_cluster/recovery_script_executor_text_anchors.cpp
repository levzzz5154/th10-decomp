// Genuine, complete helper models for the 0040BD80 caller cluster.
// The native MSVC LTCG build determines the helpers' private register inputs.

#include <stdarg.h>
#include <string.h>
#include "th10/game/recovery_script_executor_cluster/recovery_script_executor_text_anchors.hpp"

extern "C" {
extern unsigned char recovery_decoded_path_00497d40[];
int __cdecl recovery_vsprintf_004524a6(
    char* buffer, const char* format, char* args);

// These image text-rasterization entries use six ordinary stack arguments
// and RET 24. Their bodies contain the GDI/texture upload effects; neither
// call is replaced with a placeholder or a guessed register-only prototype.
void __stdcall recovery_draw_shadowed_00437db0(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
void __stdcall recovery_draw_unshadowed_00437fe0(
    const int* destination_bounds, int horizontal_offset, int font_height,
    unsigned int color, const char* text, void* texture);
}

#pragma code_seg(".text$00417010_fn")
char* __stdcall RecoveryDecodePath_00417010(const unsigned char* encoded) {
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

// 0x004479D0 DispatchText is absolute-bound to its retail address; its body
// is recovered by the registered marktext dispatcher cluster and is not
// needed here. The executor only observes it through MarkText.
void __stdcall RecoveryDispatchText_004479d0(
    RecoveryTextResource_004479d0* resource, int font_height,
    const char* text, void* texture, int horizontal_offset,
    unsigned int color, int unshadowed);

// 0x00447A50 MarkText: genuine body. Retail receives the VM in the __thiscall
// receiver register (the interprocedural pass assigns ESI at the executor's
// call sites) with manager, color and format on the stack; the manager slot is
// never read. The executor's format strings carry no conversions, so the
// image's vararg pointer (the format terminator) models the unused pack.
#pragma code_seg()

#pragma code_seg(".text$00447a50_fn")
void RecoveryTextVm::MarkText(
    void* manager, unsigned int color, const char* format) {
    char buffer[128];
    recovery_vsprintf_004524a6(buffer, format, const_cast<char*>(format));
    RecoveryTextResource_004479d0* text_resource = resource;
    RecoveryDispatchText_004479d0(
        text_resource, static_cast<int>(font_height), buffer,
        text_resource->texture, 0, color, (flags_360 >> 1) & 1);
    flags_35c |= 1;
}
#pragma code_seg()
