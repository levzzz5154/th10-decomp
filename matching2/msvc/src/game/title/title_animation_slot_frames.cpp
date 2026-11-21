// 0x0042C6D0..0x0042C770: Title::ClearAnimationSlot, Title::SetSlotFrame
#include "th10/game/title_menu.hpp"

extern "C" void* g_sprt_ctrl;

static __forceinline TitleAnmVm* FindAnimationSlot(int slot_value) {
    AnimationScriptId id = { slot_value };
    return static_cast<TitleAnmVm*>(
        reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id));
}

static __forceinline void SetAnimationTreeFrame(
        TitleAnmVm* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (TitleAnmChild* child = object->children;
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
void Title::SetSlotFrame(int index, short frame) {
    SetAnimationTreeFrame(FindAnimationSlot(animation_slots[index].value), frame);
}
#pragma code_seg()
