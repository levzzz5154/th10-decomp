#include "../../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_caller_00433ef0.hpp"

extern "C" void* g_sprt_ctrl;

static __forceinline RecoveryMusicVm_00433ef0* FindAnimationSlot(unsigned int handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle) };
    return static_cast<RecoveryMusicVm_00433ef0*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id));
}

static __forceinline void SetAnimationTreeFrame(
        RecoveryMusicVm_00433ef0* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

#pragma code_seg(".text$0042c6d0_fn")
void Title::ClearAnimationSlot(int index) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index]), 1);
    animation_slots[index] = 0;
}
#pragma code_seg(".text$0042c770_fn")
void Title::SetSlotFrame(int index, unsigned short frame) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index]), frame);
}
#pragma code_seg()
