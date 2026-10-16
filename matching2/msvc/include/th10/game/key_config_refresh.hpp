#ifndef TH10_KEY_CONFIG_REFRESH_0042F8B0_HPP
#define TH10_KEY_CONFIG_REFRESH_0042F8B0_HPP
#include <stddef.h>
struct KeyConfigResource { unsigned char reserved[0x200]; };
struct KeyConfigMatrix {
    float values[4][4];
    __forceinline void SetIdentity();
};
struct KeyConfigAnimationObject;
struct KeyConfigChildNode {
    KeyConfigAnimationObject* object;
    KeyConfigChildNode* next;
    KeyConfigChildNode* previous;
};
struct KeyConfigAnimationObject {
    int handle;
    unsigned char reserved_004[0x10 - 0x04];
    KeyConfigChildNode children_010;
    unsigned char reserved_01c[0x4C - 0x1C];
    float width;
    float height;
    unsigned char reserved_054[0x23C - 0x054];
    KeyConfigMatrix block_a;
    KeyConfigMatrix block_copy;
    KeyConfigMatrix block_b;
    unsigned char reserved_2fc[0x308 - 0x2FC];
    KeyConfigResource* resource;
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;
    unsigned char reserved_386[0x38A - 0x386];
    short script_tag_38a;
    unsigned char reserved_38c[0x394 - 0x38C];
    unsigned char* record;
};
struct KeyConfigLookupContext {
    unsigned char reserved[0x72DAD4];
    KeyConfigChildNode* primary_bucket;
    int reserved_72dad8;
    KeyConfigChildNode* secondary_bucket;
};
// A four-byte aggregate preserves the retail lookup's single stack argument.
struct KeyConfigScriptId { int value; };
class KeyConfigAnimationManager {
public:
    __declspec(noinline) void* __fastcall Find(KeyConfigLookupContext* context,
                                               KeyConfigScriptId id);
};
extern "C" KeyConfigLookupContext* g_sprt_ctrl;
struct TitleKeyConfigView {
    unsigned char reserved_000[0x2CC];
    KeyConfigScriptId parent_handle_2cc;
    unsigned char reserved_2d0[0x59CC - 0x2D0];
    short bindings_59cc[5];
    __forceinline int FindChildHandle(unsigned short tag, KeyConfigLookupContext* context);
    __forceinline KeyConfigAnimationObject* FindDigit(unsigned short tag);
};
// The full configuration body is compiled as an ABI anchor in the driver.
// Its explicit parameter order yields resource ECX, object EAX and index EDX.
extern "C" __declspec(noinline) int __stdcall ConfigureKeyConfigDigit2(
    KeyConfigResource* resource, KeyConfigAnimationObject* object, int index);
// MSVC 7.1-compatible compile-time checks for the observed retail overlays.
typedef char KeyConfigParentHandleOffsetCheck[
    offsetof(TitleKeyConfigView, parent_handle_2cc) == 0x2CC ? 1 : -1];
typedef char KeyConfigBindingsOffsetCheck[
    offsetof(TitleKeyConfigView, bindings_59cc) == 0x59CC ? 1 : -1];
typedef char KeyConfigChildListOffsetCheck[
    offsetof(KeyConfigAnimationObject, children_010) == 0x10 ? 1 : -1];
typedef char KeyConfigResourceOffsetCheck[
    offsetof(KeyConfigAnimationObject, resource) == 0x308 ? 1 : -1];
typedef char KeyConfigTagOffsetCheck[
    offsetof(KeyConfigAnimationObject, script_tag_38a) == 0x38A ? 1 : -1];
typedef char KeyConfigChildLinkSizeCheck[
    sizeof(KeyConfigChildNode) == 12 ? 1 : -1];
#endif
