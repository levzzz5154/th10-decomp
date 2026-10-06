#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

struct TriggerPositionObject {
    unsigned char reserved_000[0x14];
    struct TriggerPositionLink* children;
    int children_flagged;
    unsigned char reserved_01c[0x340 - 0x1C];
    DispatcherVec3 position;
};
struct TriggerPositionLink {
    TriggerPositionObject* object;
    TriggerPositionLink* next;
};
typedef char TriggerPositionOffset[
    offsetof(TriggerPositionObject, position)==0x340?1:-1];

#pragma code_seg(".text$004492f0_fn")
void DispatcherSetPosition(AnimationLookupContext* context,
        const DispatcherVec3* position, AnimationScriptId id) {
    TriggerPositionObject* object = reinterpret_cast<TriggerPositionObject*>(
        AnimationManager_Find_004491c0(context, id));
    if (object) {
        object->position = *position;
        if (!object->children_flagged)
            for (TriggerPositionLink* child = object->children;
                 child; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg()

