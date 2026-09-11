// 0x00418AB0: load the object field at +0x40.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418ab0 {
    unsigned char pad_000[0x40];
    int field_040;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00418ab0_size_must_fit[sizeof(ObjectAccessor_00418ab0) == 0x44 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00418ab0::LoadValue() const {
    return field_040;
}
#pragma code_seg()
