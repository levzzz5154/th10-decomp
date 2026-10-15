// 0x00417710: test bit 3 of the word at +0x2A18
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417710 {
    unsigned char pad_000[0x2A18];
    unsigned int field_2A18;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417710::LoadFlag() const {
    return (field_2A18 >> 3) & 1u;
}
#pragma code_seg()
