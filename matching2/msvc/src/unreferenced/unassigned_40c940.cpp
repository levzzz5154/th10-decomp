// 0x0040C940: zero the three +0x0/+0x4/+0x8 fields
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c940 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c940::Clear() {
    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
}
#pragma code_seg()
