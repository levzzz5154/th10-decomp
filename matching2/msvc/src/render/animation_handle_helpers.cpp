// 0x00449210 and 0x004492F0: set the stop frame or the position of an
// animation and of its children, looked up by handle.
#include "../../layout/ltcg/player_state_collision_runtime/movement.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/animation_tree.hpp"

#pragma code_seg(".text$f00449210F")
void __fastcall Animation_SetStopFrame(
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
void __fastcall Animation_SetPosition(
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
#pragma code_seg()
