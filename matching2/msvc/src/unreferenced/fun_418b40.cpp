// 0x00418B40: store the object field at +0x58.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418b40 {
    unsigned char pad_000[0x58];
    int field_058;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00418b40_size_must_fit[sizeof(ObjectAccessor_00418b40) == 0x5c ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b40::StoreValue(int value) {
    field_058 = value;
}
#pragma code_seg()
