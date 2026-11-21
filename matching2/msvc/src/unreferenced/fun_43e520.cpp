// 0x0043E520: load the object field at +0x90.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0043e520 {
    unsigned char pad_000[0x90];
    int field_090;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0043e520_size_must_fit[sizeof(ObjectAccessor_0043e520) == 0x94 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0043e520::LoadValue() const {
    return field_090;
}
#pragma code_seg()
