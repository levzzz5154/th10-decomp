// 0x0040B510: read bit 1 of the +0x20 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b510 {
    unsigned char pad_000[0x20];
    unsigned int field_020;                 // +0x20
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b510::LoadValue() const {
    return (field_020 >> 1) & 1;
}
#pragma code_seg()
