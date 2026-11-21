// 0x004458A0: load the object field at +0x2fc.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004458a0 {
    unsigned char pad_000[0x2fc];
    int field_2fc;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004458a0_size_must_fit[sizeof(ObjectAccessor_004458a0) == 0x300 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004458a0::LoadValue() const {
    return field_2fc;
}
#pragma code_seg()
