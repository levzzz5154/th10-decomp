// 0x004176C0: store the object field at +0x0.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004176c0 {
    int field_000;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_004176c0_size_must_fit[sizeof(ObjectAccessor_004176c0) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004176c0::StoreValue(int value) {
    field_000 = value;
}
#pragma code_seg()
