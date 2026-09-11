// 0x0043E530: load the object field at +0xc.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0043e530 {
    unsigned char pad_000[0xc];
    int field_00c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0043e530_size_must_fit[sizeof(ObjectAccessor_0043e530) == 0x10 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0043e530::LoadValue() const {
    return field_00c;
}
#pragma code_seg()
