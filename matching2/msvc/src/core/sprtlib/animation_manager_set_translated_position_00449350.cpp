#include "th10/render/position_setter_pair.hpp"

// 0x00449350: translate x/y, copy z, and apply the same position to children.
#pragma code_seg(".text$50translated")
void __fastcall SetAnimationTranslatedPosition(
        const PositionVector* position, PositionLookupContext* context,
        PositionScriptId id) {
    PositionEntry* entry = reinterpret_cast<PositionEntry*>(
        reinterpret_cast<PositionManager*>(context)->Find(context, id));
    if (entry != 0) {
        entry->position.x = position->x + 224.0f;
        entry->position.y = position->y + 16.0f;
        entry->position.z = position->z;
        if (!entry->children_flagged) {
            for (PositionEntry* child = entry->children; child; child = child->next) {
                PositionVector* destination = &child->object->position;
                destination->x = position->x + 224.0f;
                destination->y = position->y + 16.0f;
                destination->z = position->z;
            }
        }
    }
}
#pragma code_seg()
