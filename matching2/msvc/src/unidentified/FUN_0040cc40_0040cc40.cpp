// 0x40cc40: load the pointer at +0x4, then the dword at +0x4
// through it. The object pointer arrives in EAX, which only a native LTCG
// link chooses, so this region is compiled as a cluster
// (load_deref_0040cc40.json).

struct LoadDeref_0040cc40 {
    unsigned char pad_00000[0x4];
    int field_00004; // +0x4
    __declspec(noinline) int Load() const;
};
typedef char LoadDeref_0040cc40_size_must_fit[sizeof(LoadDeref_0040cc40) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01load0040cc40")
int LoadDeref_0040cc40::Load() const {
    const unsigned char* inner = (const unsigned char*)field_00004;
    return *(const int*)(inner + 0x4);
}
#pragma code_seg()
