// 0x0044DD30: load the object field at +0x2c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0044dd30 {
    unsigned char pad_000[0x2c];
    int field_02c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0044dd30_size_must_fit[sizeof(ObjectAccessor_0044dd30) == 0x30 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0044dd30::LoadValue() const {
    return field_02c;
}
#pragma code_seg()
