// 0x00405BA0: load the +0x40 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405ba0 {
    unsigned char pad_000[0x40];
    float field_40;                          // +0x40
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405ba0::LoadValue() const {
    return field_40;
}
#pragma code_seg()
