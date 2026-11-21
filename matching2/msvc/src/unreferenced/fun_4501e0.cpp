// 0x004501E0: store the object field at +0x102c.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004501e0 {
    unsigned char pad_000[0x102c];
    int field_102c;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_004501e0_size_must_fit[sizeof(ObjectAccessor_004501e0) == 0x1030 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004501e0::StoreValue(int value) {
    field_102c = value;
}
#pragma code_seg()
