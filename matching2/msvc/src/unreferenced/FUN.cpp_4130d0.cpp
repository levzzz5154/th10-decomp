// 0x004130D0: store the object field at +0x10.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004130d0 {
    unsigned char pad_000[0x10];
    int field_010;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_004130d0_size_must_fit[sizeof(ObjectAccessor_004130d0) == 0x14 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004130d0::StoreValue(int value) {
    field_010 = value;
}
#pragma code_seg()
