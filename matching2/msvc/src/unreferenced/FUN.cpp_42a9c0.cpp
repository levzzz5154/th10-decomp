// 0x42a9c0: store one dword and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (dword_store.json).

struct dwordmark {
    unsigned char pad_00000[0x4];
    int field_00004; // +0x4
    __declspec(noinline) void Store();
};
typedef char dwordmark_0042a9c0_size_must_fit[sizeof(dwordmark) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01store0042a9c0")
void dwordmark::Store() {
    field_00004 = 0;
}
#pragma code_seg()
