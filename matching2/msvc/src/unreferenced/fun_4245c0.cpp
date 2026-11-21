// 0x004245C0: load the object field at +0x14.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004245c0 {
    unsigned char pad_000[0x14];
    int field_014;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004245c0_size_must_fit[sizeof(ObjectAccessor_004245c0) == 0x18 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004245c0::LoadValue() const {
    return field_014;
}
#pragma code_seg()
