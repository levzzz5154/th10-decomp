// 0x0041BE70: load the sign-extended word field at +0x384
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041be70 {
    unsigned char pad_000[0x384];
    short field_384;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041be70::LoadValue() const {
    return field_384;
}
#pragma code_seg()
