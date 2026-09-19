// 0x00412F40: load the float field at +0x24
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f40 {
    unsigned char pad_000[0x24];
    float field_024;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f40::LoadValue() const {
    return field_024;
}
#pragma code_seg()
