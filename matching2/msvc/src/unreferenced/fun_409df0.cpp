// 0x00409DF0: load the object field at +0x8994.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409df0 {
    unsigned char pad_000[0x8994];
    int field_8994;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409df0_size_must_fit[sizeof(ObjectAccessor_00409df0) == 0x8998 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409df0::LoadValue() const {
    return field_8994;
}
#pragma code_seg()
