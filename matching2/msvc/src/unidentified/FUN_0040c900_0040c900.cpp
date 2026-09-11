// 0x0040C900: store the object field at +0x8.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040c900 {
    unsigned char pad_000[0x8];
    int field_008;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0040c900_size_must_fit[sizeof(ObjectAccessor_0040c900) == 0xc ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c900::StoreValue(int value) {
    field_008 = value;
}
#pragma code_seg()
