// 0x0040CDA0: load the object field at +0x458.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040cda0 {
    unsigned char pad_000[0x458];
    int field_458;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040cda0_size_must_fit[sizeof(ObjectAccessor_0040cda0) == 0x45c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cda0::LoadValue() const {
    return field_458;
}
#pragma code_seg()
