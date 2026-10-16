// 0x00404F20: clear bit 0 of +0x35C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00404f20 {
    unsigned char pad_000[0x35C];
    unsigned int field_35c;                 // +0x35C
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00404f20::ClearValue() {
    field_35c &= ~1u;
}
#pragma code_seg()
