// 0x0042C830: load the object field at +0x3ec.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0042c830 {
    unsigned char pad_000[0x3ec];
    int field_3ec;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0042c830_size_must_fit[sizeof(ObjectAccessor_0042c830) == 0x3f0 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0042c830::LoadValue() const {
    return field_3ec;
}
#pragma code_seg()
