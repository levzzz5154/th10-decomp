// 0x00412FC0: product of the floats at +0x50 and +0x40
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fc0 {
    unsigned char pad_000[0x40];
    float field_040;
    unsigned char pad_044[0xC];
    float field_050;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fc0::LoadValue() const {
    return field_050 * field_040;
}
#pragma code_seg()
