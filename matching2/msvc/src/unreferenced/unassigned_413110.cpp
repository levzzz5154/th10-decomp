// 0x00413110: load the float field at +0x00
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413110 {
    float field_000;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00413110::LoadValue() const {
    return field_000;
}
#pragma code_seg()
