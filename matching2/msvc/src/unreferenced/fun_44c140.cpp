// 0x44c140: store one dword and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (dword_store2.json).

struct dwordmark2 {
    unsigned char pad_00000[0xC];
    int field_0000C; // +0xc
    __declspec(noinline) void Store();
};
typedef char dwordmark_0044c140_size_must_fit[sizeof(dwordmark2) == 0x10 ? 1 : -1];

#pragma code_seg(".text$01store0044c140")
void dwordmark2::Store() {
    field_0000C = 1;
}
#pragma code_seg()
