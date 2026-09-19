// 0x00408790: read bit 2 of +0x58 via or-fold.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408790 {
    unsigned char pad_000[0x58];
    unsigned int field_058;                 // +0x58
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00408790::LoadValue() const {
    return ((field_058 >> 2) | field_058) & 1;
}
#pragma code_seg()
