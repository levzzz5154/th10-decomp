// 0x00441FD0: store the object field at +0x24.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00441fd0 {
    unsigned char pad_000[0x24];
    int field_024;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00441fd0_size_must_fit[sizeof(ObjectAccessor_00441fd0) == 0x28 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00441fd0::StoreValue(int value) {
    field_024 = value;
}
#pragma code_seg()
