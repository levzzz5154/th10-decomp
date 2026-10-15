// 0x00412EE0: load the object field at +0x58.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00412ee0 {
    unsigned char pad_000[0x58];
    int field_058;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00412ee0_size_must_fit[sizeof(ObjectAccessor_00412ee0) == 0x5c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00412ee0::LoadValue() const {
    return field_058;
}
#pragma code_seg()
