// 0x004130F0: load the float field at +0x04
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004130f0 {
    unsigned char pad_000[0x4];
    float field_004;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_004130f0::LoadValue() const {
    return field_004;
}
#pragma code_seg()
