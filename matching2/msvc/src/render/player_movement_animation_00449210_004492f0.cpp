// Complete helpers at 0x449210, 0x4492F0 and 0x449350. The lookup takes
// only its real context and ID; no unused implicit receiver is introduced.
#include "../../layout/ltcg/player_movement_runtime/movement.hpp"
struct MovementChildNode {
    Entity* object;
    MovementChildNode* next;
};
struct MovementAnimationTree {
    unsigned char reserved_000[0x14];
    MovementChildNode* children;
    int children_flagged;
};

#pragma code_seg(".text$f00449210F")
void __fastcall MovementStopFrame_00449210(
    unsigned short frame, PickupAnimationLists* context, AnimationRef id) {
    Entity* object = reinterpret_cast<Entity*>(context->Find(id));
    if (object != 0) {
        object->StopFrame() = static_cast<short>(frame);
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0)
            for (MovementChildNode* child = tree->children; child != 0; child = child->next)
                child->object->StopFrame() = static_cast<short>(frame);
    }
}
#pragma code_seg(".text$f004492f0F")
void __fastcall MovementSetPosition_004492f0(
    const Vector3* position, PickupAnimationLists* context, AnimationRef id) {
    Entity* object = reinterpret_cast<Entity*>(context->Find(id));
    if (object != 0) {
        object->position = *position;
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0)
            for (MovementChildNode* child = tree->children; child != 0; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg(".text$f00449350F")
void __fastcall MovementSetTranslatedPosition_00449350(
    const Vector3* position, PickupAnimationLists* context, AnimationRef id) {
    Entity* object = reinterpret_cast<Entity*>(context->Find(id));
    if (object != 0) {
        object->position.x = position->x + 224.0f;
        object->position.y = position->y + 16.0f;
        object->position.z = position->z;
        MovementAnimationTree* tree = reinterpret_cast<MovementAnimationTree*>(object);
        if (tree->children_flagged == 0) {
            for (MovementChildNode* child = tree->children; child != 0; child = child->next) {
                Vector3* output = &child->object->position;
                output->x = position->x + 224.0f;
                output->y = position->y + 16.0f;
                output->z = position->z;
            }
        }
    }
}
#pragma code_seg()
