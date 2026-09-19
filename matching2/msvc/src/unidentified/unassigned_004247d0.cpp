// 0x004247D0..0x004247D9 (10 bytes): clear bit 0 of the flag dword at +0x80.
//
// Sibling of 0x004247C0 on the same class shape: retail materialises the result
// in EAX before the in-place clear.  The object arrives in ECX, so this is a
// plain __thiscall member.

struct FlagOwner_004247d0 {
    unsigned char unknown_00[0x80];
    unsigned int flags;                     // +0x80

    __declspec(noinline) FlagOwner_004247d0* ClearFlag();
};

#pragma code_seg(".text$01clear")
FlagOwner_004247d0* FlagOwner_004247d0::ClearFlag() {
    FlagOwner_004247d0* self = this;
    flags &= ~1u;
    return self;
}
#pragma code_seg()
