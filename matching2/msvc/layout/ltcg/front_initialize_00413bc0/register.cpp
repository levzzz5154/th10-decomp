// 0x004489D0: append an animation to the primary list and assign its nonzero ID.
#include "th10/game/front_initialize_00413bc0.hpp"

#pragma code_seg(".text$004489d0_fn")
FrontAnimationId FrontAnimationLists::RegisterPrimaryBack(Entity *object) {
    FrontAnimationListNode *node =
        reinterpret_cast<FrontAnimationListNode *>(&object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        FrontAnimationListNode *tail = primary_tail;
        FrontAnimationListNode *next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    ++next_id;
    if (next_id == FrontAnimationId(0))
        ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
