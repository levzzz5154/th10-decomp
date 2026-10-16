// 0x00436810: load the object field at +0x100.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436810 {
    unsigned char pad_000[0x100];
    int field_100;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436810_size_must_fit[sizeof(ObjectAccessor_00436810) == 0x104 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436810::LoadValue() const {
    return field_100;
}
#pragma code_seg()
