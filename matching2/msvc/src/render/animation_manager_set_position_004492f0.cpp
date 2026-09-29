#include "th10/render/position_setter_pair.hpp"

// 0x004492F0: copy the position to the animation and unflagged child list.
#pragma code_seg(".text$30position")
void __fastcall SetAnimationPosition_004492f0(
        const PositionVector_004492f0* position, PositionLookupContext_004492f0* context,
        PositionScriptId_004492f0 id) {
    PositionEntry_004492f0* entry = reinterpret_cast<PositionEntry_004492f0*>(
        reinterpret_cast<PositionManager_004492f0*>(context)->Find(context, id));
    if (entry != 0) {
        entry->position = *position;
        if (!entry->children_flagged)
            for (PositionEntry_004492f0* child = entry->children; child; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg()
