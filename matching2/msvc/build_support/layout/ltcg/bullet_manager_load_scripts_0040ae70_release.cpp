// Unselected native ABI anchor from src/core/sprtlib/fun_00447810_00447810.cpp.
// Only the placement section differs.
class SprtCtrl {
public:
    void MarkResourceForRemoval(void* resource);
};

extern "C" SprtCtrl* g_sprt_ctrl;

// CRT free, the entry at 0x00452422 (0x004524A1 is the five-byte jump to it).
extern "C" void __cdecl crt_free(void* memory);

// One entry's animation interface.  Retail calls its third virtual slot (+0x8)
// with the interface itself pushed, i.e. a __stdcall member.
struct AnimationHandle_00447810 {
    virtual void slot0();
    virtual void slot1();
    virtual void __stdcall slot2();
};

struct AnimationResourceEntry_00447810 {
    AnimationHandle_00447810* handle;   // +0x00
    void* allocation;                   // +0x04
    unsigned char pad_008[8];
};

struct AnimationResource_00447810 {
    unsigned char pad_000[0x108];
    void* resource_108;                            // +0x108: the record's own interface
    int entry_count_10c;                           // +0x10C
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;                           // +0x118
    void* auxiliary_11c;                           // +0x11C
    AnimationResourceEntry_00447810* entries_120;  // +0x120
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;                           // +0x12C

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$00hd_release")
void AnimationResource_00447810::Release() {
    if (resource_108 == 0)
        return;
    g_sprt_ctrl->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry_00447810* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            crt_free(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        crt_free(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        crt_free(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        crt_free(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        crt_free(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        crt_free(resource_108);
        resource_108 = 0;
    }
}
#pragma code_seg()
