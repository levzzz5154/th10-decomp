// 0x00418B50: clear 0x4 in the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418b50 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void ClearFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b50::ClearFlag() {
    field_060 &= ~0x4u;
}
#pragma code_seg()
