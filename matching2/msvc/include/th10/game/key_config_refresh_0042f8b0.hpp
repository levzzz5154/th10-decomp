#ifndef TH10_KEY_CONFIG_REFRESH_0042F8B0_HPP
#define TH10_KEY_CONFIG_REFRESH_0042F8B0_HPP
#include <stddef.h>
struct KeyConfigResource_0042f8b0 { unsigned char reserved[0x200]; };
struct KeyConfigMatrix_0042f8b0 {
    float values[4][4];
    __forceinline void SetIdentity();
};
struct KeyConfigAnimationObject_0042f8b0;
struct KeyConfigChildNode_0042f8b0 {
    KeyConfigAnimationObject_0042f8b0* object;
    KeyConfigChildNode_0042f8b0* next;
    KeyConfigChildNode_0042f8b0* previous;
};
struct KeyConfigAnimationObject_0042f8b0 {
    int handle;
    unsigned char reserved_004[0x10 - 0x04];
    KeyConfigChildNode_0042f8b0 children_010;
    unsigned char reserved_01c[0x4C - 0x1C];
    float width;
    float height;
    unsigned char reserved_054[0x23C - 0x054];
    KeyConfigMatrix_0042f8b0 block_a;
    KeyConfigMatrix_0042f8b0 block_copy;
    KeyConfigMatrix_0042f8b0 block_b;
    unsigned char reserved_2fc[0x308 - 0x2FC];
    KeyConfigResource_0042f8b0* resource;
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;
    unsigned char reserved_386[0x38A - 0x386];
    short script_tag_38a;
    unsigned char reserved_38c[0x394 - 0x38C];
    unsigned char* record;
};
struct KeyConfigLookupContext_0042f8b0 {
    unsigned char reserved[0x72DAD4];
    KeyConfigChildNode_0042f8b0* primary_bucket;
    int reserved_72dad8;
    KeyConfigChildNode_0042f8b0* secondary_bucket;
};
// A four-byte aggregate preserves the retail lookup's single stack argument.
struct KeyConfigScriptId_0042f8b0 { int value; };
class KeyConfigAnimationManager_0042f8b0 {
public:
    __declspec(noinline) void* __fastcall Find(KeyConfigLookupContext_0042f8b0* context,
                                               KeyConfigScriptId_0042f8b0 id);
};
extern "C" KeyConfigLookupContext_0042f8b0* data_00491c10;
struct KeyConfigLabels_0042f8b0 {
    unsigned char reserved_000[0x2CC];
    KeyConfigScriptId_0042f8b0 parent_handle_2cc;
    unsigned char reserved_2d0[0x59CC - 0x2D0];
    short bindings_59cc[5];
    __forceinline int FindChildHandle(unsigned short tag, KeyConfigLookupContext_0042f8b0* context);
    __forceinline KeyConfigAnimationObject_0042f8b0* FindDigit(unsigned short tag);
};
// The full configuration body is compiled as an ABI anchor in the driver.
// Its explicit parameter order yields resource ECX, object EAX and index EDX.
extern "C" __declspec(noinline) int __stdcall ConfigureKeyConfigDigit_0043e5a0(
    KeyConfigResource_0042f8b0* resource, KeyConfigAnimationObject_0042f8b0* object, int index);
// MSVC 7.1-compatible compile-time checks for the observed retail overlays.
typedef char KeyConfigParentHandleOffsetCheck_0042f8b0[
    offsetof(KeyConfigLabels_0042f8b0, parent_handle_2cc) == 0x2CC ? 1 : -1];
typedef char KeyConfigBindingsOffsetCheck_0042f8b0[
    offsetof(KeyConfigLabels_0042f8b0, bindings_59cc) == 0x59CC ? 1 : -1];
typedef char KeyConfigChildListOffsetCheck_0042f8b0[
    offsetof(KeyConfigAnimationObject_0042f8b0, children_010) == 0x10 ? 1 : -1];
typedef char KeyConfigResourceOffsetCheck_0042f8b0[
    offsetof(KeyConfigAnimationObject_0042f8b0, resource) == 0x308 ? 1 : -1];
typedef char KeyConfigTagOffsetCheck_0042f8b0[
    offsetof(KeyConfigAnimationObject_0042f8b0, script_tag_38a) == 0x38A ? 1 : -1];
typedef char KeyConfigChildLinkSizeCheck_0042f8b0[
    sizeof(KeyConfigChildNode_0042f8b0) == 12 ? 1 : -1];
#endif
