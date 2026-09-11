// 0x00436820: load the object field at +0x114.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436820 {
    unsigned char pad_000[0x114];
    int field_114;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436820_size_must_fit[sizeof(ObjectAccessor_00436820) == 0x118 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436820::LoadValue() const {
    return field_114;
}
#pragma code_seg()
