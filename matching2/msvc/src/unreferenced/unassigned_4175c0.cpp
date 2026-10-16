// 0x004175C0: set 0x4 in the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004175c0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004175c0::SetFlag() {
    field_060 |= 0x4u;
}
#pragma code_seg()
