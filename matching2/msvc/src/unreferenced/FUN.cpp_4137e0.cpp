// 0x004137E0: load the object field at +0x10.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004137e0 {
    unsigned char pad_000[0x10];
    int field_010;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_004137e0_size_must_fit[sizeof(ObjectAccessor_004137e0) == 0x14 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004137e0::LoadValue() const {
    return field_010;
}
#pragma code_seg()
