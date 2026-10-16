// 0x004489D0: append an animation to the primary list and assign its nonzero ID.
#include "th10/game/result_overlay.hpp"

#pragma code_seg(".text$004489d0_fn")
ResultAnimationId ResultAnimationLists::RegisterPrimaryBack(Entity* object) {
    CaptionNode* node = reinterpret_cast<CaptionNode*>(
        &object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        CaptionNode* tail = primary_tail;
        CaptionNode* next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    ++next_id;
    if (next_id == ResultAnimationId(0)) ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
