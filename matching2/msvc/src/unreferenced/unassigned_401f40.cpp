// 0x00401F40: arm the +0x0/+0x4/+0x8 timer fields (previous sentinel, cleared others)
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401f40 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Arm();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401f40::Arm() {
    field_4 = 0;
    field_0 = 0xFFF0BDC1;
    field_8 = 0;
}
#pragma code_seg()
