// 0x00447810..0x004478F6: retire one cached animation-resource record.
//
// Retail enters with the record in EDI - every one of its 24 call sites loads
// it there - and hands the record to SprtCtrl::MarkResourceForRemoval
// with the manager singleton in EAX and the record in EDX.  Neither convention
// is expressible as a declaration: an external callee keeps the convention its
// prototype names, and no MSVC convention puts an argument in EAX.  Both are
// choices of the native /LTCG pass, so this model lives in the same
// whole-program link as that helper: the merged
// build_support/layout/ltcg/animation_manager_mark_resource_for_removal.json
// cluster, whose driver carries the synthetic caller that establishes the
// record in EDI.
//
// The loop holds a pointer to the current entry instead of re-indexing the
// array.  Retail keeps that pointer live in ESI across the interface release
// and the free; that is the pressure which moves the receiver out of ESI and
// into EDI.

#include "th10/render/animation_resource_removal.hpp"

extern "C" SprtCtrl* g_sprt_ctrl;

// CRT free, the entry at 0x00452422 (0x004524A1 is the five-byte jump to it).
extern "C" void __cdecl crt_free(void* memory);

#include "th10/game/enemy_manager_dependencies.hpp"

#pragma code_seg(".text$05b")
void AnimationResource6::Release() {
    if (resource_108 == 0)
        return;
    g_sprt_ctrl->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry* entry = &entries_120[index];
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
