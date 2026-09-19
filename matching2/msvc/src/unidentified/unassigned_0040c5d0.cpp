// 0x0040C5D0: zero the +0x1000/+0x1004 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c5d0 {
    unsigned char pad_000[0x1000];
    int field_1000;
    int field_1004;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c5d0::Clear() {
    field_1000 = 0;
    field_1004 = 0;
}
#pragma code_seg()
