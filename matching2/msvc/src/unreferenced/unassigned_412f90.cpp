// 0x00412F90: load the float field at +0x1C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f90 {
    unsigned char pad_000[0x1C];
    float field_01C;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f90::LoadValue() const {
    return field_01C;
}
#pragma code_seg()
