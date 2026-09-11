// 0x00418B70: store the object field at +0x30.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418b70 {
    unsigned char pad_000[0x30];
    int field_030;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00418b70_size_must_fit[sizeof(ObjectAccessor_00418b70) == 0x34 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b70::StoreValue(int value) {
    field_030 = value;
}
#pragma code_seg()
