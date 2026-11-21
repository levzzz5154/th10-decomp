// 0x004367F0: load the object field at +0x0.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004367f0 {
    int field_000;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004367f0_size_must_fit[sizeof(ObjectAccessor_004367f0) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004367f0::LoadValue() const {
    return field_000;
}
#pragma code_seg()
