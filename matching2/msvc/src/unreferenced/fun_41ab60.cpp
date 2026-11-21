// 0x0041AB60: load the object field at +0x24.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ab60 {
    unsigned char pad_000[0x24];
    int field_024;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0041ab60_size_must_fit[sizeof(ObjectAccessor_0041ab60) == 0x28 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041ab60::LoadValue() const {
    return field_024;
}
#pragma code_seg()
