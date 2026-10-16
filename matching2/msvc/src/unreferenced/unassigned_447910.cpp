// 0x00447910..0x00447939: release one entry of an animation resource - its
// interface through the third virtual slot, then its allocation.  This is the
// out-of-line copy of the per-entry block 0x00447810 inlines; it is compiled in
// the same native-LTCG cluster, whose pass hands it the entry in ESI.

extern "C" void __cdecl crt_free(void* memory);

struct AnimationHandle9 {
    virtual void slot0();
    virtual void slot1();
    virtual void __stdcall slot2();
};

struct AnimationResourceEntry {
    AnimationHandle9* handle;   // +0x00
    void* allocation;                   // +0x04
    unsigned char pad_008[8];

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$15layoutb")
void AnimationResourceEntry::Release() {
    if (handle != 0) {
        handle->slot2();
        handle = 0;
    }
    if (allocation != 0) {
        crt_free(allocation);
        allocation = 0;
    }
}
#pragma code_seg()
