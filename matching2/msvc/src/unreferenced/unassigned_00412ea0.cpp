// 0x00412EA0: load the sign-extended object field at +0x38A.
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412ea0 {
    unsigned char pad_000[0x38A];
    short field_38A;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00412ea0::LoadValue() const {
    return field_38A;
}
#pragma code_seg()
