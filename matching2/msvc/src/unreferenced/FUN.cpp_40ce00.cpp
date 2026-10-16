// 0x0040CE00: store the object field at +0x9e90.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0040ce00 {
    unsigned char pad_000[0x9e90];
    int field_9e90;
    __declspec(noinline) void StoreValue(int value);
};
typedef char ObjectAccessor_0040ce00_size_must_fit[sizeof(ObjectAccessor_0040ce00) == 0x9e94 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ce00::StoreValue(int value) {
    field_9e90 = value;
}
#pragma code_seg()
