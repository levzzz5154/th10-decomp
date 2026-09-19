// 0x00412FB0: product of the floats at +0x4C and +0x3C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fb0 {
    unsigned char pad_000[0x3C];
    float field_03C;
    unsigned char pad_040[0xC];
    float field_04C;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fb0::LoadValue() const {
    return field_04C * field_03C;
}
#pragma code_seg()
