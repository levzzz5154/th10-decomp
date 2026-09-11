// 0x00417580: store the object field at +0x5c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417580 {
    unsigned char pad_000[0x5c];
    int field_05c;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_00417580_size_must_fit[sizeof(ObjectAccessor_00417580) == 0x60 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00417580::StoreValue(int value) {
    field_05c = value;
}
#pragma code_seg()
