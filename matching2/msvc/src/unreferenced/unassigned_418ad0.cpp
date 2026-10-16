// 0x00418AD0: assign bit 3 of the word at +0x60 from the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418ad0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetBit3(unsigned int mask);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418ad0::SetBit3(unsigned int mask) {
    field_060 = (field_060 & ~8u) | ((mask & 1u) << 3);
}
#pragma code_seg()
