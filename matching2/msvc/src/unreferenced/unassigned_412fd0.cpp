// 0x00412FD0: load the float field at +0x08
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fd0 {
    unsigned char pad_000[0x8];
    float field_008;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fd0::LoadValue() const {
    return field_008;
}
#pragma code_seg()
