// 0x00418BD0: store the object field at +0x4.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418bd0 {
    unsigned char pad_000[0x4];
    int field_004;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00418bd0_size_must_fit[sizeof(ObjectAccessor_00418bd0) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418bd0::StoreValue(int value) {
    field_004 = value;
}
#pragma code_seg()
