// 0x004020F0: clear bit 0 of +0x40.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004020f0 {
    unsigned char pad_000[0x40];
    unsigned int field_040;                 // +0x40
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004020f0::ClearValue() {
    field_040 &= ~1u;
}
#pragma code_seg()
