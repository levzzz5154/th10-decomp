// 0x00405CA0: load the object field at +0x3e0b50.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00405ca0 {
    unsigned char pad_000[0x3e0b50];
    int field_3e0b50;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00405ca0_size_must_fit[sizeof(ObjectAccessor_00405ca0) == 0x3e0b54 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00405ca0::LoadValue() const {
    return field_3e0b50;
}
#pragma code_seg()
