// 0x0040C8F0: load the object field at +0x8.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040c8f0 {
    unsigned char pad_000[0x8];
    int field_008;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040c8f0_size_must_fit[sizeof(ObjectAccessor_0040c8f0) == 0xc ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c8f0::LoadValue() const {
    return field_008;
}
#pragma code_seg()
