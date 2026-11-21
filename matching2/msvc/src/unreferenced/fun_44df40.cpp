// 0x0044DF40: load the object field at +0x1000.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0044df40 {
    unsigned char pad_000[0x1000];
    int field_1000;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0044df40_size_must_fit[sizeof(ObjectAccessor_0044df40) == 0x1004 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0044df40::LoadValue() const {
    return field_1000;
}
#pragma code_seg()
