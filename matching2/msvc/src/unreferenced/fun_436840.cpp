// 0x00436840: load the object field at +0x104.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436840 {
    unsigned char pad_000[0x104];
    int field_104;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436840_size_must_fit[sizeof(ObjectAccessor_00436840) == 0x108 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436840::LoadValue() const {
    return field_104;
}
#pragma code_seg()
