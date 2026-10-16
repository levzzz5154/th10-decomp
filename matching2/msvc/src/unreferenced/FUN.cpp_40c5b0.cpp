// 0x0040C5B0: load the object field at +0x50.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040c5b0 {
    unsigned char pad_000[0x50];
    int field_050;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040c5b0_size_must_fit[sizeof(ObjectAccessor_0040c5b0) == 0x54 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c5b0::LoadValue() const {
    return field_050;
}
#pragma code_seg()
