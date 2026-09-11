// 0x0040C5C0: load the object field at +0x34.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040c5c0 {
    unsigned char pad_000[0x34];
    int field_034;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040c5c0_size_must_fit[sizeof(ObjectAccessor_0040c5c0) == 0x38 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c5c0::LoadValue() const {
    return field_034;
}
#pragma code_seg()
