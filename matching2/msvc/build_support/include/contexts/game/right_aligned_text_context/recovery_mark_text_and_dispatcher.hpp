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
    unsigned char reserved_018[0x1C];
    float width;                           // +034
};

struct RecoveryTextVm {
    unsigned char reserved_000[0x35C];
    unsigned int flags_35c;
    unsigned int flags_360;
    unsigned char reserved_364[0x30];
    RecoveryTextResource* resource; // +394
    unsigned char reserved_398[8];
    unsigned char font_height;              // +3A0

    // manager occupies the first retail stack home but is not read by this
    // body. Varargs remain cdecl; the native caller cluster chooses ESI for this.
    __declspec(noinline) void __cdecl MarkText(
        void* manager, ...);
};

typedef char RecoveryTextResourceWidthOffsetCheck[
    offsetof(RecoveryTextResource, width) == 0x34 ? 1 : -1];
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
__declspec(noinline) void __stdcall RecoveryDispatchText2(
    RecoveryTextResource* resource, void* texture,
    int horizontal_offset, int font_height, unsigned int color,
    const char* text, int unshadowed);

#endif
