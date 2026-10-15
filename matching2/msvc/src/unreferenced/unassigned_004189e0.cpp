// 0x004189E0: clear the four state words at +0x4C..+0x58
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004189e0 {
    unsigned char pad_000[0x4C];
    int field_04C;
    int field_050;
    int field_054;
    int field_058;
    __declspec(noinline) void ClearState();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004189e0::ClearState() {
    field_050 = 0;
    field_054 = 0;
    field_04C = 0;
    field_058 = 0;
}
#pragma code_seg()
