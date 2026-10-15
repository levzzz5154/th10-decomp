// 0x00418B10: assign bit 0 of the word at +0x60 from the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418b10 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetBit0(unsigned int mask);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b10::SetBit0(unsigned int mask) {
    field_060 = (field_060 & ~1u) | (mask & 1u);
}
#pragma code_seg()
