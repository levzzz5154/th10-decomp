// 0x00413770: set 0x20 in the word at +0x9EB4
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413770 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413770::SetFlag() {
    field_9EB4 |= 0x20u;
}
#pragma code_seg()
