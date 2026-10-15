// 0x00409F80: load the object field at +0x54.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409f80 {
    unsigned char pad_000[0x54];
    int field_054;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409f80_size_must_fit[sizeof(ObjectAccessor_00409f80) == 0x58 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409f80::LoadValue() const {
    return field_054;
}
#pragma code_seg()
