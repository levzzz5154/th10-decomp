// 0x0040CDB0: load the object field at +0x3504.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040cdb0 {
    unsigned char pad_000[0x3504];
    int field_3504;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0040cdb0_size_must_fit[sizeof(ObjectAccessor_0040cdb0) == 0x3508 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cdb0::LoadValue() const {
    return field_3504;
}
#pragma code_seg()
