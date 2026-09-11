// 0x0041ACA0: load the object field at +0x45c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041aca0 {
    unsigned char pad_000[0x45c];
    int field_45c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0041aca0_size_must_fit[sizeof(ObjectAccessor_0041aca0) == 0x460 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041aca0::LoadValue() const {
    return field_45c;
}
#pragma code_seg()
