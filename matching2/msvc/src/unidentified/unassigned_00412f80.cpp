// 0x00412F80: load the float field at +0x18
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f80 {
    unsigned char pad_000[0x18];
    float field_018;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f80::LoadValue() const {
    return field_018;
}
#pragma code_seg()
