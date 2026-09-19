// 0x0041AB00: return +0x4C when +0x44 is set, otherwise +0x48
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041ab00 {
    unsigned char pad_000[0x44];
    unsigned int field_044;
    int field_048;
    int field_04C;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041ab00::LoadValue() const {
    return field_044 ? field_04C : field_048;
}
#pragma code_seg()
