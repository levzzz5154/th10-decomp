// 0x0044DF50: store the object field at +0x1000.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0044df50 {
    unsigned char pad_000[0x1000];
    int field_1000;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0044df50_size_must_fit[sizeof(ObjectAccessor_0044df50) == 0x1004 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0044df50::StoreValue(int value) {
    field_1000 = value;
}
#pragma code_seg()
