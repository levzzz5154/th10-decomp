
extern "C" void __cdecl crt_free_startup(void* block);

struct AnimationSlot2 {
    unsigned char pad_000[0x40];
    void* field_40;
    void* field_44;
    void* field_48;
    void* field_4c;
    void* field_50;
    __declspec(noinline) void ReleaseRetail();
};

__declspec(noinline) AnimationSlot2* DestroySlot(
        AnimationSlot2* slot, unsigned int flags);

#pragma code_seg(".text$03destroy")
__declspec(noinline) AnimationSlot2* DestroySlot(
        AnimationSlot2* slot, unsigned int flags) {
    slot->ReleaseRetail();
    if (flags & 1) crt_free_startup(slot);
    return slot;
}
#pragma code_seg()
