// 0x00412F30: load the float field at +0x20
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f30 {
    unsigned char pad_000[0x20];
    float field_020;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f30::LoadValue() const {
    return field_020;
}
#pragma code_seg()
