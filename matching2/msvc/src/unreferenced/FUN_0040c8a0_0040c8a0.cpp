// 0x0040C8A0: store the object field at +0x0.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040c8a0 {
    int field_000;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0040c8a0_size_must_fit[sizeof(ObjectAccessor_0040c8a0) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c8a0::StoreValue(int value) {
    field_000 = value;
}
#pragma code_seg()
