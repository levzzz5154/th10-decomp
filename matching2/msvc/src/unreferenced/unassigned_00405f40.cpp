
extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" char* data_00491c10;

struct AnimationResource_00405f40 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_114[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    __declspec(noinline) void Release();
};

__declspec(noinline) int ReleaseCachedResource_00405f40();

#pragma code_seg(".text$01release")
__declspec(noinline) int ReleaseCachedResource_00405f40() {
    AnimationResource_00405f40** slot =
        (AnimationResource_00405f40**)(data_00491c10 + 0x3AD088);
    AnimationResource_00405f40* record = *slot;
    if (record != 0) {
        record->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
