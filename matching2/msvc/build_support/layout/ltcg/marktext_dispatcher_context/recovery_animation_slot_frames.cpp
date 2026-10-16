#include "../../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_caller_433ef0.hpp"

extern "C" void* g_sprt_ctrl;

static __forceinline RecoveryMusicVm* FindAnimationSlot(unsigned int handle) {
    RecoveryScriptId id = { static_cast<int>(handle) };
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
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index]), 1);
    animation_slots[index] = 0;
}
#pragma code_seg(".text$0042c770_fn")
void Title::SetSlotFrame(int index, unsigned short frame) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index]), frame);
}
#pragma code_seg()
