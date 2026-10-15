// 0x00401D90: zero the +0x896C/+0x8970 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401d90 {
    unsigned char pad_000[0x896C];
    int field_896c;
    int field_8970;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401d90::Clear() {
    field_896c = 0;
    field_8970 = 0;
}
#pragma code_seg()
