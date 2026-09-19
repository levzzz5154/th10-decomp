// 0x00417740: store the double argument at +0x2C and return it
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00417740 {
    unsigned char pad_000[0x2C];
    double field_02C;
    __declspec(noinline) double StoreValue(double value);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
double ObjectAccessor_00417740::StoreValue(double value) {
    field_02C = value;
    return value;
}
#pragma code_seg()
