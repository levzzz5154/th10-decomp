// 0x00442120: store the object field at +0x44.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00442120 {
    unsigned char pad_000[0x44];
    int field_044;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00442120_size_must_fit[sizeof(ObjectAccessor_00442120) == 0x48 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00442120::StoreValue(int value) {
    field_044 = value;
}
#pragma code_seg()
