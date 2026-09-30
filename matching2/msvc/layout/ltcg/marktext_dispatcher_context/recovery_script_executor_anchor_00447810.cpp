// 0x00447810..0x004478F6: retire one cached animation-resource record.
//
// Retail enters with the record in EDI - every one of its 24 call sites loads
// it there - and hands the record to AnimationManager::MarkResourceForRemoval
// with the manager singleton in EAX and the record in EDX.  Neither convention
// is expressible as a declaration: an external callee keeps the convention its
// prototype names, and no MSVC convention puts an argument in EAX.  Both are
// choices of the native /LTCG pass, so this model lives in the same
// whole-program link as that helper: the merged
// layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json
// cluster, whose driver carries the synthetic caller that establishes the
// record in EDI.
//
// The loop holds a pointer to the current entry instead of re-indexing the
// array.  Retail keeps that pointer live in ESI across the interface release
// and the free; that is the pressure which moves the receiver out of ESI and
// into EDI.

class AnimationManager {
public:
    void MarkResourceForRemoval(void* resource);
};

extern "C" AnimationManager* data_00491c10;

// CRT free, the entry at 0x00452422 (0x004524A1 is the five-byte jump to it).
extern "C" void __cdecl entry_free_00452422(void* memory);

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

#pragma code_seg(".text$00447810_fn")
void AnimationResource_00447810::Release() {
    if (resource_108 == 0)
        return;
    data_00491c10->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry_00447810* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            entry_free_00452422(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        entry_free_00452422(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        entry_free_00452422(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        entry_free_00452422(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        entry_free_00452422(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        entry_free_00452422(resource_108);
        resource_108 = 0;
    }
}
#pragma code_seg()
