// 0x0040AE40: load the object field at +0x4.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040ae40 {
    unsigned char pad_000[0x4];
    int field_004;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040ae40_size_must_fit[sizeof(ObjectAccessor_0040ae40) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040ae40::LoadValue() const {
    return field_004;
}
#pragma code_seg()
