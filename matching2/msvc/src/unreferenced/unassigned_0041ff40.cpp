// 0x0041FF40: test bit 4 of the word at +0x150
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041ff40 {
    unsigned char pad_000[0x150];
    unsigned int field_150;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_0041ff40::LoadFlag() const {
    return (field_150 >> 4) & 1u;
}
#pragma code_seg()
