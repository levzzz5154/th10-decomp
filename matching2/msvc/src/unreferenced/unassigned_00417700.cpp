// 0x00417700: set 0x2 in the word at +0x35C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417700 {
    unsigned char pad_000[0x35C];
    unsigned int field_35C;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00417700::SetFlag() {
    field_35C |= 0x2u;
}
#pragma code_seg()
