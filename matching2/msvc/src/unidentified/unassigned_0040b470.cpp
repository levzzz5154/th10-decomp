// 0x0040B470: read bit 2 of the +0x74 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b470 {
    unsigned char pad_000[0x74];
    unsigned int field_074;                 // +0x74
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b470::LoadValue() const {
    return (field_074 >> 2) & 1;
}
#pragma code_seg()
