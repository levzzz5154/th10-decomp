// 0x00449350 (src/render/animation_manager_set_translated_position_00449350.cpp),
// present so its callers see its register convention. Compiler context only.
#include "movement.hpp"
#include "animation_tree.hpp"

#pragma code_seg(".text$f00449350F")
void __fastcall Animation_SetTranslatedPosition(
    PickupAnimationLists* context, const Vector3* position, AnimationRef id) {
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
