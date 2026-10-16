// 0x0041AB50: load the object field at +0x12c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ab50 {
    unsigned char pad_000[0x12c];
    int field_12c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0041ab50_size_must_fit[sizeof(ObjectAccessor_0041ab50) == 0x130 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041ab50::LoadValue() const {
    return field_12c;
}
#pragma code_seg()
