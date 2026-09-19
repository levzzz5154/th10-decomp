// 0x00412F60: load bit 0 of the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f60 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00412f60::LoadFlag() const {
    return field_028 & 1u;
}
#pragma code_seg()
