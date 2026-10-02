// Complete helpers at 0x449210, 0x4492F0 and 0x449350. The lookup takes
// only its real context and ID; no unused implicit receiver is introduced.
#include "th10/game/pause_result_open_004231d0/player/movement/movement.hpp"
struct MovementChildNode {
    Entity* object;
    MovementChildNode* next;
};
struct MovementAnimationTree {
    unsigned char reserved_000[0x14];
    MovementChildNode* children;
    int children_flagged;
};

#pragma code_seg(".text$00449210_fn")
void __fastcall MovementStopFrame_00449210(
    unsigned short frame, AnimationLookupContext* context, AnimationScriptId id) {
    Entity* object = static_cast<Entity*>(AnimationManager_Find_004491c0(context, id));
    if (object != 0) {
        object->StopFrame() = static_cast<short>(frame);
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0)
            for (MovementChildNode* child = tree->children; child != 0; child = child->next)
                child->object->StopFrame() = static_cast<short>(frame);
    }
}
#pragma code_seg(".text$004492f0_fn")
void __fastcall MovementSetPosition_004492f0(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id) {
    Entity* object = static_cast<Entity*>(AnimationManager_Find_004491c0(context, id));
    if (object != 0) {
        object->position = *position;
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0)
            for (MovementChildNode* child = tree->children; child != 0; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg(".text$00449350_fn")
void __fastcall MovementSetTranslatedPosition_00449350(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id) {
    Entity* object = static_cast<Entity*>(AnimationManager_Find_004491c0(context, id));
    if (object != 0) {
        object->position.x = position->x + 224.0f;
        object->position.y = position->y + 16.0f;
        object->position.z = position->z;
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0) {
            for (MovementChildNode* child = tree->children; child != 0; child = child->next) {
                child->object->position.x = position->x + 224.0f;
                child->object->position.y = position->y + 16.0f;
                child->object->position.z = position->z;
            }
        }
    }
}
#pragma code_seg()
