// 0x00436800: load the object field at +0x120.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436800 {
    unsigned char pad_000[0x120];
    int field_120;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436800_size_must_fit[sizeof(ObjectAccessor_00436800) == 0x124 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436800::LoadValue() const {
    return field_120;
}
#pragma code_seg()
