// 0x004136A0: load the object field at +0x390.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004136a0 {
    unsigned char pad_000[0x390];
    int field_390;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004136a0_size_must_fit[sizeof(ObjectAccessor_004136a0) == 0x394 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004136a0::LoadValue() const {
    return field_390;
}
#pragma code_seg()
