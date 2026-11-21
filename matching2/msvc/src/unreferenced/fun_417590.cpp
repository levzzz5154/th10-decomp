// 0x00417590: load the object field at +0x5c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417590 {
    unsigned char pad_000[0x5c];
    int field_05c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00417590_size_must_fit[sizeof(ObjectAccessor_00417590) == 0x60 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00417590::LoadValue() const {
    return field_05c;
}
#pragma code_seg()
