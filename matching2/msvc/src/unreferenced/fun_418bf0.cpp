// 0x00418BF0: store the object field at +0x34.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418bf0 {
    unsigned char pad_000[0x34];
    int field_034;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00418bf0_size_must_fit[sizeof(ObjectAccessor_00418bf0) == 0x38 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418bf0::StoreValue(int value) {
    field_034 = value;
}
#pragma code_seg()
