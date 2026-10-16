// 0x0040C710: stamp the +0x0 vtable word and clear the +0x1010/+0x1014 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c710 {
    int field_0;
    unsigned char pad_004[0x100C];
    int field_1010;
    int field_1014;
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c710::Init() {
    field_0 = 0x46D0D8;
    field_1010 = 0;
    field_1014 = 0;
}
#pragma code_seg()
