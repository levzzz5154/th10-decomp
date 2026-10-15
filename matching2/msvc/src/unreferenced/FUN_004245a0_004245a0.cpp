// 0x004245A0: store the object field at +0x8988.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004245a0 {
    unsigned char pad_000[0x8988];
    int field_8988;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_004245a0_size_must_fit[sizeof(ObjectAccessor_004245a0) == 0x898c ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004245a0::StoreValue(int value) {
    field_8988 = value;
}
#pragma code_seg()
