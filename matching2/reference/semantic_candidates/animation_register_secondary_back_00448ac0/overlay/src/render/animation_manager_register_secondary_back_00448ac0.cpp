// 0x00448AC0: append an animation to the primary list and assign its nonzero ID.
#include "th10/game/player_hud_animations.hpp"

#pragma code_seg(".text$00448ac0_fn")
AnimationRef AnimationLists::RegisterSecondaryBack(Entity* object) {
    AnimationListNode* node = reinterpret_cast<AnimationListNode*>(
        &object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!secondary_head)
        secondary_head = node;
    else {
        AnimationListNode* tail = secondary_tail;
        AnimationListNode* next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    secondary_tail = node;
    ++next_id;
    if (next_id == 0) ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
