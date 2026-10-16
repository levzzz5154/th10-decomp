// 0x00401F90: store the argument in +0x0 and clear +0x4/+0x8
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401f90 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Set(int value);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401f90::Set(int value) {
    field_0 = value;
    field_4 = 0;
    field_8 = 0;
}
#pragma code_seg()
