// 0x0040CDF0: load the object field at +0x78.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040cdf0 {
    unsigned char pad_000[0x78];
    int field_078;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040cdf0_size_must_fit[sizeof(ObjectAccessor_0040cdf0) == 0x7c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cdf0::LoadValue() const {
    return field_078;
}
#pragma code_seg()
