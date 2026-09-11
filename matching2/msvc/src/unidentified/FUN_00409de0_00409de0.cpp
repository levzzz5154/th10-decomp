// 0x00409DE0: load the object field at +0x899c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00409de0 {
    unsigned char pad_000[0x899c];
    int field_899c;
    __declspec(noinline) int LoadValue() const;
};
typedef char ObjectAccessor_00409de0_size_must_fit[sizeof(ObjectAccessor_00409de0) == 0x89a0 ? 1 : -1];

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00409de0::LoadValue() const {
    return field_899c;
}
#pragma code_seg()
