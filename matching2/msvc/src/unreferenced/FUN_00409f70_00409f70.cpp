// 0x409f70: load the pointer at +0x54, then the dword at +0x8
// through it. The object pointer arrives in EAX, which only a native LTCG
// link chooses, so this region is compiled as a cluster
// (load_deref_00409f70.json).

struct LoadDeref_00409f70 {
    unsigned char pad_00000[0x54];
    int field_00054; // +0x54
    __declspec(noinline) int Load() const;
};
typedef char LoadDeref_00409f70_size_must_fit[sizeof(LoadDeref_00409f70) == 0x58 ? 1 : -1];

#pragma code_seg(".text$01load00409f70")
int LoadDeref_00409f70::Load() const {
    const unsigned char* inner = (const unsigned char*)field_00054;
    return *(const int*)(inner + 0x8);
}
#pragma code_seg()
