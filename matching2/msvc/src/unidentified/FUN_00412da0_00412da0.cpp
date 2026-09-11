// 0x00412DA0: store the object field at +0x34.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00412da0 {
    unsigned char pad_000[0x34];
    int field_034;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00412da0_size_must_fit[sizeof(ObjectAccessor_00412da0) == 0x38 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00412da0::StoreValue(int value) {
    field_034 = value;
}
#pragma code_seg()
