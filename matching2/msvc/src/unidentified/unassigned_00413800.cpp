// 0x00413800: complement bit 0 of the word at +0x2480
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413800 {
    unsigned char pad_000[0x2480];
    unsigned int field_2480;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00413800::LoadFlag() const {
    return ~field_2480 & 1u;
}
#pragma code_seg()
