// 0x004087C0: read bit 1 of the +0x58 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004087c0 {
    unsigned char pad_000[0x58];
    unsigned int field_058;                 // +0x58
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004087c0::LoadValue() const {
    return (field_058 >> 1) & 1;
}
#pragma code_seg()
