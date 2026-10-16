// 0x00409DC0: load the object field at +0x44.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409dc0 {
    unsigned char pad_000[0x44];
    int field_044;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409dc0_size_must_fit[sizeof(ObjectAccessor_00409dc0) == 0x48 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409dc0::LoadValue() const {
    return field_044;
}
#pragma code_seg()
