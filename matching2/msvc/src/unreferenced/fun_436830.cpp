// 0x00436830: load the object field at +0x110.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436830 {
    unsigned char pad_000[0x110];
    int field_110;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436830_size_must_fit[sizeof(ObjectAccessor_00436830) == 0x114 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436830::LoadValue() const {
    return field_110;
}
#pragma code_seg()
