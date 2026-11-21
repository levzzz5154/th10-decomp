// 0x0040AC10: store the object field at +0x8974.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040ac10 {
    unsigned char pad_000[0x8974];
    int field_8974;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0040ac10_size_must_fit[sizeof(ObjectAccessor_0040ac10) == 0x8978 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ac10::StoreValue(int value) {
    field_8974 = value;
}
#pragma code_seg()
