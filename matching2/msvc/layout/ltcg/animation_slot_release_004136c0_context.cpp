// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_slot_release_004136c0.cpp"

#include "animation_lookup_anchors.cpp"

#pragma code_seg(".text$06context")
extern "C" int __stdcall AnimationSlotReleaseContext_004136c0(AnimationSlot_004136c0* slots, int count) {
    for (int i = 0; i < count; ++i)
        slots[i].Release();
    return count;
}
#pragma code_seg()
