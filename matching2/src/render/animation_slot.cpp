// 0x004136C0 FUN_004136c0
// Readable reconstruction of retail helper FUN_004136c0.
//
// FUN_004136c0 is the per-slot animation-batch teardown invoked by the
// entity destructor pair 0x00414370 / 0x00414570 (both of which feed a
// 16-byte aligned slot record stored at Entity +0x9EB8).  The retail
// helper takes the slot pointer in ECX and the animation manager in EDI,
// then walks six 4-byte animation handles (offsets 0x40, 0x44, 0x48,
// 0x4c, 0x50, 0x54 of the slot) invoking FUN_004492a0 on each nonzero
// handle and clearing the slot word afterwards.  FUN_004492a0 is the
// readable AnimationManager_MarkForRemovalAndClearHandle helper already
// reconstructed in animation_manager.cpp.

#include "th10/render/animation_slot.hpp"
#include "th10/render/animation_manager.hpp"


#include <cstdint>



void AnimationSlot_Release(void* slot, void* animation_manager) {
    if (slot == 0) return;
    uint32_t* handles = static_cast<uint32_t*>(slot);
    // The slot layout stores six animation handles at 4-byte stride
    // starting at offset 0x40 (word offset 0x10).  Each nonzero handle
    // is flagged for removal via AnimationManager_SetFlag (the readable
    // twin of FUN_004492a0), and the slot's word is then explicitly
    // zeroed by the caller — the retail helper does not clear the slot.
    static const unsigned int kSlotHandleWordOffsets[] = {
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    };
    for (unsigned int i = 0; i < 6; ++i) {
        uint32_t* handle = &handles[kSlotHandleWordOffsets[i]];
        if (*handle != 0) {
            AnimationManager_SetFlag(
                animation_manager,
                static_cast<int>(*handle),
                0x04000000u);
        }
        *handle = 0;
    }
}
