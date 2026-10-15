// 0x00417640: load the object field at +0x18.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417640 {
    unsigned char pad_000[0x18];
    int field_018;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00417640_size_must_fit[sizeof(ObjectAccessor_00417640) == 0x1c ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00417640::LoadValue() const {
    return field_018;
}
#pragma code_seg()
