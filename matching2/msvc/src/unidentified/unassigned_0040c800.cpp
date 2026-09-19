// 0x0040C800: zero the +0x1008/+0x100C pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c800 {
    unsigned char pad_000[0x1008];
    int field_1008;
    int field_100c;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c800::Clear() {
    field_1008 = 0;
    field_100c = 0;
}
#pragma code_seg()
