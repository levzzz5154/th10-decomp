// 0x004053A0: read bit 0 of the +0x60 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_004053a0 {
    unsigned char pad_000[0x60];
    unsigned int field_60;                    // +0x60
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004053a0::LoadValue() const {
    return field_60 & 1;
}
#pragma code_seg()
