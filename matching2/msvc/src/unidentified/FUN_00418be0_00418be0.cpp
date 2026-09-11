// 0x00418BE0: store the object field at +0x50.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418be0 {
    unsigned char pad_000[0x50];
    int field_050;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00418be0_size_must_fit[sizeof(ObjectAccessor_00418be0) == 0x54 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418be0::StoreValue(int value) {
    field_050 = value;
}
#pragma code_seg()
