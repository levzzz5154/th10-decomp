// 0x00436850: load the object field at +0x108.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00436850 {
    unsigned char pad_000[0x108];
    int field_108;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00436850_size_must_fit[sizeof(ObjectAccessor_00436850) == 0x10c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00436850::LoadValue() const {
    return field_108;
}
#pragma code_seg()
