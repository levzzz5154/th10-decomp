// 0x0042C7C0 (25 bytes): look up the child with script id `script_id` under
// the state's animation slot (the ID table at +0x2C4, stride four).
//
// Native LTCG passes the state in EAX, the slot in ECX and the script id in
// EBX; only the hidden result pointer is on the stack.
#include "th10/render/animation_stop_run.hpp"

// Interface of 0x004497D0 (src/core/sprtlib/animation_manager_find_child_by_script_index.cpp).
struct AnimationRef2 {
    int value;
    AnimationRef2(int value) : value(value) {}
};
struct AnimationHandle15 {
    AnimationScriptId id;
    __declspec(noinline) AnimationRef2 FindChildRef(int script_id);
};

#pragma code_seg(".text$47dispatchz3")
__declspec(noinline) AnimationRef2 __fastcall Title_FindAnimationSlotChild(
        int slot, Title* state, int script_id) {
    return reinterpret_cast<AnimationHandle15*>(&AnimationSlots(state)[slot])
        ->FindChildRef(script_id);
}
#pragma code_seg()
