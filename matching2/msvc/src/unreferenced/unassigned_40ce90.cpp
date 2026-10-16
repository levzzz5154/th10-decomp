// 0x0040CE90: raise bit 3 of +0x378C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040ce90 {
    unsigned char pad_000[0x378C];
    unsigned int field_378c;                 // +0x378C
    __declspec(noinline) void SetValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ce90::SetValue() {
    field_378c |= 8u;
}
#pragma code_seg()
