// 0x00405490: load the +0x8 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405490 {
    unsigned char pad_000[0x8];
    float field_8;                          // +0x8
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405490::LoadValue() const {
    return field_8;
}
#pragma code_seg()
