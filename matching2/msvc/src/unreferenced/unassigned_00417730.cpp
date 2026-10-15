// 0x00417730: store the double argument at +0x24 and return it
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00417730 {
    unsigned char pad_000[0x24];
    double field_024;
    __declspec(noinline) double StoreValue(double value);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
double ObjectAccessor_00417730::StoreValue(double value) {
    field_024 = value;
    return value;
}
#pragma code_seg()
