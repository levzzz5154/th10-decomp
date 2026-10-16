
extern "C" void __cdecl crt_free_startup(void* block);
extern "C" char* g_sprt_ctrl;

struct AnimationResource3 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_114[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    __declspec(noinline) void Release();
};

__declspec(noinline) int ReleaseCachedResource2();

#pragma code_seg(".text$01release")
__declspec(noinline) int ReleaseCachedResource2() {
    AnimationResource3** slot =
        (AnimationResource3**)(g_sprt_ctrl + 0x3AD084);
    AnimationResource3* record = *slot;
    if (record != 0) {
        record->Release();
        crt_free_startup(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
