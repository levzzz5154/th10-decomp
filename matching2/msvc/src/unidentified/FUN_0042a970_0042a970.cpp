// 0x0042A970: store the object field at +0x2c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0042a970 {
    unsigned char pad_000[0x2c];
    int field_02c;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0042a970_size_must_fit[sizeof(ObjectAccessor_0042a970) == 0x30 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0042a970::StoreValue(int value) {
    field_02c = value;
}
#pragma code_seg()
