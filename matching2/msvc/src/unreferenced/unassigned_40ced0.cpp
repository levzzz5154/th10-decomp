// 0x0040CED0: read bit 3 of the +0x378C flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040ced0 {
    unsigned char pad_000[0x378C];
    unsigned int field_378c;                 // +0x378C
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040ced0::LoadValue() const {
    return (field_378c >> 3) & 1;
}
#pragma code_seg()
