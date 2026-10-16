// 0x00413730: load the object field at +0x9e80.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00413730 {
    unsigned char pad_000[0x9e80];
    int field_9e80;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00413730_size_must_fit[sizeof(ObjectAccessor_00413730) == 0x9e84 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00413730::LoadValue() const {
    return field_9e80;
}
#pragma code_seg()
