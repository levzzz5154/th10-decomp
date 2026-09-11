// 0x0044DF60: load the object field at +0x102c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0044df60 {
    unsigned char pad_000[0x102c];
    int field_102c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0044df60_size_must_fit[sizeof(ObjectAccessor_0044df60) == 0x1030 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0044df60::LoadValue() const {
    return field_102c;
}
#pragma code_seg()
