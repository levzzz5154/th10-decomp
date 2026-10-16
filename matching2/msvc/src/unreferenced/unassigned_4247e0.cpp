// 0x004247E0..0x004247E6 (7 bytes): clear bit 0 of the flag dword at +0x54.
//
// Third of the flag-clearing accessors (see 0x004247C0, 0x004247D0).  ECX is
// the object, so the body compiles as a plain __thiscall member.

struct FlagOwner3 {
    unsigned char unknown_00[0x54];
    unsigned int flags;                     // +0x54

    __declspec(noinline) FlagOwner3* ClearFlag();
};

#pragma code_seg(".text$01clear")
FlagOwner3* FlagOwner3::ClearFlag() {
    FlagOwner3* self = this;
    flags &= ~1u;
    return self;
}
#pragma code_seg()
