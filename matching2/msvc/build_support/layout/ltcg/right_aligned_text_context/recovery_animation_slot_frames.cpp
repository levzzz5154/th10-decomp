#include "../../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller_433ef0.hpp"

extern "C" void* g_sprt_ctrl;

static __forceinline RecoveryMusicVm* FindAnimationSlot(int slot_value) {
    AnimationScriptId id = { slot_value };
    return static_cast<RecoveryMusicVm*>(
        reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
}

static __forceinline void SetAnimationTreeFrame(
        RecoveryMusicVm* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

#pragma code_seg(".text$0042c6d0_fn")
void Title::ClearAnimationSlot(int index) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index].value), 1);
    animation_slots[index].value = 0;
}
#pragma code_seg(".text$0042c770_fn")
void Title::SetSlotFrame(int index, unsigned short frame) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index].value), frame);
}
#pragma code_seg()
