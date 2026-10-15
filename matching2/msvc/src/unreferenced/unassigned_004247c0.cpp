// 0x004247C0..0x004247C6 (7 bytes): clear bit 0 of the flag dword at +0x10.
//
// Retail materialises the result register first (`mov eax,ecx`) and then clears
// the bit through that copy, returning the object.  ECX is the object, so the
// body is an ordinary __thiscall member and compiles as a plain translation
// unit; the value returned is the receiver itself.

struct FlagOwner_004247c0 {
    unsigned char unknown_00[0x10];
    unsigned int flags;                     // +0x10

    __declspec(noinline) FlagOwner_004247c0* ClearFlag();
};

#pragma code_seg(".text$01clear")
FlagOwner_004247c0* FlagOwner_004247c0::ClearFlag() {
    FlagOwner_004247c0* self = this;
    flags &= ~1u;
    return self;
}
#pragma code_seg()
