// 0x004088B0: load the object field at +0x9ec8.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004088b0 {
    unsigned char pad_000[0x9ec8];
    int field_9ec8;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004088b0_size_must_fit[sizeof(ObjectAccessor_004088b0) == 0x9ecc ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004088b0::LoadValue() const {
    return field_9ec8;
}
#pragma code_seg()
