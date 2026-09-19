// 0x00412F50: set bit 0 of the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f50 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00412f50::SetFlag() {
    field_028 |= 1u;
}
#pragma code_seg()
