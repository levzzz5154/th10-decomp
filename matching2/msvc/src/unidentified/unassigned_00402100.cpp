// 0x00402100: clear bit 0 of +0x30.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402100 {
    unsigned char pad_000[0x30];
    unsigned int field_030;                 // +0x30
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402100::ClearValue() {
    field_030 &= ~1u;
}
#pragma code_seg()
