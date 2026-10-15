// 0x00424600: load the object field at +0x8998.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00424600 {
    unsigned char pad_000[0x8998];
    int field_8998;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00424600_size_must_fit[sizeof(ObjectAccessor_00424600) == 0x899c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00424600::LoadValue() const {
    return field_8998;
}
#pragma code_seg()
