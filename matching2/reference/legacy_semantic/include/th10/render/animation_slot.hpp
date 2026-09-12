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
//
// The retail helper is a __fastcall with a single parameter; the readable
// signature below keeps the slot in the first parameter and exposes the
// manager explicitly because the C ABI does not carry EDI across the
// call to a single-arg __fastcall without a register convention.

#ifndef TH10_RENDER_ANIMATION_SLOT_HPP
#define TH10_RENDER_ANIMATION_SLOT_HPP

// Release the six animation handles stored at offsets 0x40, 0x44, 0x48,
// 0x4c, 0x50, 0x54 of ``slot``.  Each nonzero handle is marked for
// removal via AnimationManager_MarkForRemovalAndClearHandle and the
// slot word is reset to zero.  Safe to call with slot == 0 (no-op).
void AnimationSlot_Release(void* slot, void* animation_manager);

#endif  // TH10_RENDER_ANIMATION_SLOT_HPP