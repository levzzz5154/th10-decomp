// 0x0041FF30: store the object field at +0x390.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ff30 {
    unsigned char pad_000[0x390];
    int field_390;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0041ff30_size_must_fit[sizeof(ObjectAccessor_0041ff30) == 0x394 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0041ff30::StoreValue(int value) {
    field_390 = value;
}
#pragma code_seg()
