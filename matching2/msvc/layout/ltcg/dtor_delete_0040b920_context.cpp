// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/unidentified/unassigned_0040b920.cpp"

// As 0x0040B3A0 reads it: a slot word at +0x40.
struct AnchorEntity_0040b920 {
    unsigned char reserved_000[0x40];
    unsigned int slot;
};

// 0x0040B3A0's body.  It is compiled only so the whole-program pass can hand it
// the object in EAX: its only caller is the modelled deleting destructor and no
// declaration names that register.  The layout's gaps place this section at the
// retail address, so the destructor's call bakes retail's own displacement.
// None of these bytes are selected as recovered code.
#pragma code_seg(".text$01anchor")
extern "C" __declspec(noinline) void __cdecl asm_FUN_0040b3a0_0040b3a0(void* object) {
    AnchorEntity_0040b920* entity = (AnchorEntity_0040b920*)object;
    entity->slot = 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040b920(Deletable_0040b920** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0040b920_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
