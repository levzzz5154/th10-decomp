// 0x00405380: load the +0x0 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405380 {
    float field_0;                          // +0x0
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405380::LoadValue() const {
    return field_0;
}
#pragma code_seg()
