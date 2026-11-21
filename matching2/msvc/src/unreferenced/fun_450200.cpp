// 0x450200: load the pointer at +0x4, then the dword at +0x4
// through it. The object pointer arrives in EAX, which only a native LTCG
// link chooses, so this region is compiled as a cluster
// (load_deref3.json).

struct LoadDeref3 {
    unsigned char pad_00000[0x4];
    int field_00004; // +0x4
    __declspec(noinline) int Load() const;
};
typedef char LoadDeref_00450200_size_must_fit[sizeof(LoadDeref3) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01load00450200")
int LoadDeref3::Load() const {
    const unsigned char* inner = (const unsigned char*)field_00004;
    return *(const int*)(inner + 0x4);
}
#pragma code_seg()
