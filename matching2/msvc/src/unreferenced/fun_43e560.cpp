// 0x0043E560: load the object field at +0x0.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0043e560 {
    int field_000;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_0043e560_size_must_fit[sizeof(ObjectAccessor_0043e560) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0043e560::LoadValue() const {
    return field_000;
}
#pragma code_seg()
