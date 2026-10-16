// 0x004131A0: test bit 3 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004131a0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_004131a0::LoadFlag() const {
    return (field_060 >> 3) & 1u;
}
#pragma code_seg()
