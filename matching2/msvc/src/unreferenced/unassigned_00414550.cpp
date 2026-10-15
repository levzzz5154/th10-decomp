
extern "C" void __cdecl entry_free_004524a1(void* block);

struct AnimationSlot_00414550 {
    unsigned char pad_000[0x40];
    void* field_40;
    void* field_44;
    void* field_48;
    void* field_4c;
    void* field_50;
    __declspec(noinline) void ReleaseRetail();
};

__declspec(noinline) AnimationSlot_00414550* DestroySlot_00414550(
        AnimationSlot_00414550* slot, unsigned int flags);

#pragma code_seg(".text$03destroy")
__declspec(noinline) AnimationSlot_00414550* DestroySlot_00414550(
        AnimationSlot_00414550* slot, unsigned int flags) {
    slot->ReleaseRetail();
    if (flags & 1) entry_free_004524a1(slot);
    return slot;
}
#pragma code_seg()
