// 0x004489D0: append an animation to the primary list and assign its nonzero ID.
#include "types.hpp"

#pragma code_seg(".text$004489d0_fn")
MovementRegisteredId MovementPrimaryLists::RegisterPrimaryBack(Entity *object) {
    AnimationManagerNodeOpen *node =
        reinterpret_cast<AnimationManagerNodeOpen *>(&object->manager_node_animation);
    node->animation = object;
    node->next = 0;
    node->previous = 0;
    if (!head)
        head = node;
    else {
        AnimationManagerNodeOpen *last = tail;
        AnimationManagerNodeOpen *next = last->next;
        if (next) {
            node->next = next;
            last->next->previous = node;
        }
        last->next = node;
        node->previous = last;
    }
    tail = node;
    ++next_id;
    if (next_id == MovementRegisteredId(0))
        ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
