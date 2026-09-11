// 0x004130A0: store the object field at +0x300.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004130a0 {
    unsigned char pad_000[0x300];
    int field_300;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_004130a0_size_must_fit[sizeof(ObjectAccessor_004130a0) == 0x304 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004130a0::StoreValue(int value) {
    field_300 = value;
}
#pragma code_seg()
