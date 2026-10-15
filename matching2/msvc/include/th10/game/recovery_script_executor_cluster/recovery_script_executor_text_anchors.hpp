#ifndef TH10_RECOVERY_SCRIPT_EXECUTOR_TEXT_ANCHORS_HPP
#define TH10_RECOVERY_SCRIPT_EXECUTOR_TEXT_ANCHORS_HPP

#include <stddef.h>

// The destination texture and pixel bounds are held in the animation resource.
// Only the observed prefix is named; its complete allocation size is unknown.
struct RecoveryTextResource {
    unsigned int reserved_000;
    void* texture;                         // +004
    float left;                            // +008
    float top;                             // +00C
    float right;                           // +010
    float bottom;                          // +014
};

struct RecoveryTextVm {
    unsigned char reserved_000[0x35C];
    unsigned int flags_35c;
    unsigned int flags_360;
    unsigned char reserved_364[0x30];
    RecoveryTextResource* resource; // +394
    unsigned char reserved_398[8];
    unsigned char font_height;              // +3A0

    // Retail passes the VM in the member receiver register (the
    // interprocedural pass assigns ESI at the executor's call sites) with the
    // manager, color and format on the stack; the body never reads the
    // manager slot.
    __declspec(noinline) void MarkText(
        void* manager, unsigned int color, const char* format);
};


typedef char RecoveryTextResourceTextureOffsetCheck[
    offsetof(RecoveryTextResource, texture) == 4 ? 1 : -1];
typedef char RecoveryTextResourceBoundsOffsetCheck[
    offsetof(RecoveryTextResource, left) == 8 ? 1 : -1];
typedef char RecoveryTextVmFlagsOffsetCheck[
    offsetof(RecoveryTextVm, flags_35c) == 0x35C ? 1 : -1];
typedef char RecoveryTextVmModeOffsetCheck[
    offsetof(RecoveryTextVm, flags_360) == 0x360 ? 1 : -1];
typedef char RecoveryTextVmResourceOffsetCheck[
    offsetof(RecoveryTextVm, resource) == 0x394 ? 1 : -1];
typedef char RecoveryTextVmFontOffsetCheck[
    offsetof(RecoveryTextVm, font_height) == 0x3A0 ? 1 : -1];

__declspec(noinline) char* __stdcall RecoveryDecodePath(
    const unsigned char* encoded);

// In the retail private ABI the resource, font and text arrive in EDI, EAX
// and EBX. Four stack operands remain, and the function returns with RET 16.
__declspec(noinline) void __stdcall RecoveryDispatchText_004479d0(
    RecoveryTextResource* resource, int font_height,
    const char* text, void* texture, int horizontal_offset,
    unsigned int color, int unshadowed);

#endif
