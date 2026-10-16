// 0x0042A980: store the object field at +0x28.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0042a980 {
    unsigned char pad_000[0x28];
    int field_028;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0042a980_size_must_fit[sizeof(ObjectAccessor_0042a980) == 0x2c ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0042a980::StoreValue(int value) {
    field_028 = value;
}
#pragma code_seg()
