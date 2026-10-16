// 0x0042B4C0..0x0042B4C6 (7 bytes): clear bit 0 of the flag dword at +0x2C.
//
// Same shape as the 0x004247C0 family: the object arrives in ECX, the result
// register is materialised before the in-place clear, and the receiver is
// returned.

struct FlagOwner4 {
    unsigned char unknown_00[0x2C];
    unsigned int flags;                     // +0x2C

    __declspec(noinline) FlagOwner4* ClearFlag();
};

#pragma code_seg(".text$01clear")
FlagOwner4* FlagOwner4::ClearFlag() {
    FlagOwner4* self = this;
    flags &= ~1u;
    return self;
}
#pragma code_seg()
