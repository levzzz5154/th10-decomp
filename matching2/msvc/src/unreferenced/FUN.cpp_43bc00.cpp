// 0x0043BC00: store the object field at +0xc.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0043bc00 {
    unsigned char pad_000[0xc];
    int field_00c;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0043bc00_size_must_fit[sizeof(ObjectAccessor_0043bc00) == 0x10 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0043bc00::StoreValue(int value) {
    field_00c = value;
}
#pragma code_seg()
