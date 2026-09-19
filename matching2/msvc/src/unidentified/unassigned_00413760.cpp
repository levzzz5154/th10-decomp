// 0x00413760: test bit 4 of the word at +0x9EB4
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413760 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00413760::LoadFlag() const {
    return (field_9EB4 >> 4) & 1u;
}
#pragma code_seg()
