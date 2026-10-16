// 0x00402220: clear bit 0 of +0x80.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402220 {
    unsigned char pad_000[0x80];
    unsigned int field_080;                 // +0x80
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402220::ClearValue() {
    field_080 &= ~1u;
}
#pragma code_seg()
