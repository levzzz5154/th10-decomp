// 0x00409F60: load the object field at +0x60.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409f60 {
    unsigned char pad_000[0x60];
    int field_060;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409f60_size_must_fit[sizeof(ObjectAccessor_00409f60) == 0x64 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409f60::LoadValue() const {
    return field_060;
}
#pragma code_seg()
