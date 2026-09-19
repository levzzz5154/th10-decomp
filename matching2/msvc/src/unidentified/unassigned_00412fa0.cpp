// 0x00412FA0: clear 0x1 in the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fa0 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) void ClearFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00412fa0::ClearFlag() {
    field_028 &= ~0x1u;
}
#pragma code_seg()
