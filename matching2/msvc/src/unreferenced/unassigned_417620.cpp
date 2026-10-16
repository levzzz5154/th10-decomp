// 0x00417620: mask the word field at +0x2C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417620 {
    unsigned char pad_000[0x2C];
    unsigned short field_02C;
    __declspec(noinline) unsigned int Mask(unsigned int mask) const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417620::Mask(unsigned int mask) const {
    return field_02C & mask;
}
#pragma code_seg()
