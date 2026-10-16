// 0x00405BB0: load the object field at +0x28.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00405bb0 {
    unsigned char pad_000[0x28];
    int field_028;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00405bb0_size_must_fit[sizeof(ObjectAccessor_00405bb0) == 0x2c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00405bb0::LoadValue() const {
    return field_028;
}
#pragma code_seg()
