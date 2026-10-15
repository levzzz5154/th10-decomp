#include "th10/render/position_setter_pair.hpp"

// 0x00449350: translate x/y, copy z, and apply the same position to children.
#pragma code_seg(".text$50translated")
void __fastcall SetAnimationTranslatedPosition_00449350(
        const PositionVector_004492f0* position, PositionLookupContext_004492f0* context,
        PositionScriptId_004492f0 id) {
    PositionEntry_004492f0* entry = reinterpret_cast<PositionEntry_004492f0*>(
        reinterpret_cast<PositionManager_004492f0*>(context)->Find(context, id));
    if (entry != 0) {
        entry->position.x = position->x + 224.0f;
        entry->position.y = position->y + 16.0f;
        entry->position.z = position->z;
        if (!entry->children_flagged) {
            for (PositionEntry_004492f0* child = entry->children; child; child = child->next) {
                PositionVector_004492f0* destination = &child->object->position;
                destination->x = position->x + 224.0f;
                destination->y = position->y + 16.0f;
                destination->z = position->z;
            }
        }
    }
}
#pragma code_seg()
