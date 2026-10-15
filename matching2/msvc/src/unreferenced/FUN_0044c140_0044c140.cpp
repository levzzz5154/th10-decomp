// 0x44c140: store one dword and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (dword_store_0044c140.json).

struct dwordmark_0044c140 {
    unsigned char pad_00000[0xC];
    int field_0000C; // +0xc
    __declspec(noinline) void Store();
};
typedef char dwordmark_0044c140_size_must_fit[sizeof(dwordmark_0044c140) == 0x10 ? 1 : -1];

#pragma code_seg(".text$01store0044c140")
void dwordmark_0044c140::Store() {
    field_0000C = 1;
}
#pragma code_seg()
