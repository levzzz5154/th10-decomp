// 0x0041AC00: store the object field at +0x34.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ac00 {
    unsigned char pad_000[0x34];
    int field_034;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0041ac00_size_must_fit[sizeof(ObjectAccessor_0041ac00) == 0x38 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0041ac00::StoreValue(int value) {
    field_034 = value;
}
#pragma code_seg()
