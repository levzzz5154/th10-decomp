// 0x00409F30: load the object field at +0x8.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409f30 {
    unsigned char pad_000[0x8];
    int field_008;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409f30_size_must_fit[sizeof(ObjectAccessor_00409f30) == 0xc ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409f30::LoadValue() const {
    return field_008;
}
#pragma code_seg()
