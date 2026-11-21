// 0x00427DF0: load the object field at +0x2c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00427df0 {
    unsigned char pad_000[0x2c];
    int field_02c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00427df0_size_must_fit[sizeof(ObjectAccessor_00427df0) == 0x30 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00427df0::LoadValue() const {
    return field_02c;
}
#pragma code_seg()
