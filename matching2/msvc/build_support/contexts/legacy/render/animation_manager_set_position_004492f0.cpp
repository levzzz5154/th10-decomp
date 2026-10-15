#include "th10/render/position_setter_pair.hpp"

// 0x004492F0: copy the position to the animation and unflagged child list.
#pragma code_seg(".text$30position")
void __fastcall SetAnimationPosition_004492f0(
        PositionLookupContext* context, const PositionVector* position,
        PositionScriptId id) {
    PositionEntry* entry = reinterpret_cast<PositionEntry*>(
        reinterpret_cast<PositionManager*>(context)->Find(context, id));
    if (entry != 0) {
        entry->position = *position;
        if (!entry->children_flagged)
            for (PositionEntry* child = entry->children; child; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg()
