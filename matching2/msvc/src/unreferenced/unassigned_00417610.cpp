// 0x00417610: mask the word field at +0x32
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417610 {
    unsigned char pad_000[0x32];
    unsigned short field_032;
    __declspec(noinline) unsigned int Mask(unsigned int mask) const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417610::Mask(unsigned int mask) const {
    return field_032 & mask;
}
#pragma code_seg()
