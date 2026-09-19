// 0x00401CA0: load the +0x3C float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401ca0 {
    unsigned char pad_000[0x3C];
    float field_3c;                          // +0x3C
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00401ca0::LoadValue() const {
    return field_3c;
}
#pragma code_seg()
