// 0x00413740: set 0x10 at +0x9EB4 and clear +0x9ECC
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413740 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    unsigned char pad_9EB8[0x14];
    unsigned int field_9ECC;
    __declspec(noinline) void SetFlagAndClear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413740::SetFlagAndClear() {
    field_9EB4 |= 0x10u;
    field_9ECC = 0;
}
#pragma code_seg()
