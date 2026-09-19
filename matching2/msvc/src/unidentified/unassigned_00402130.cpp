// 0x00402130: clear bit 0 of +0x20.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402130 {
    unsigned char pad_000[0x20];
    unsigned int field_020;                 // +0x20
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402130::ClearValue() {
    field_020 &= ~1u;
}
#pragma code_seg()
