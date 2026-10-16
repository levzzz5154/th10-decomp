// 0x00408850: raise bit 0 of the object's +0x2A18 flag word.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster whose synthetic
// caller walks an array of objects.
struct ObjectAccessor_00408850 {
    unsigned char pad_000[0x2A18];
    unsigned int field_2a18;                 // +0x2A18
    __declspec(noinline) void SetValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408850::SetValue() {
    field_2a18 |= 1u;
}
#pragma code_seg()
