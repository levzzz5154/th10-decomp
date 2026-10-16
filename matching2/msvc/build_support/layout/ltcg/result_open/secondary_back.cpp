// Complete 0x00448AC0 secondary-list insert, expressed with its genuine aggregate result.
#include "th10/game/pause_result_open/open_animation.hpp"
#pragma code_seg(".text$00448ac0_fn")
AnimationScriptId AnimationListsOpen::RegisterSecondaryBack(Entity* object) {
    AnimationManagerNodeOpen* node = reinterpret_cast<AnimationManagerNodeOpen*>(&object->manager_node_animation);
    node->animation = object;
    node->next = 0;
    node->previous = 0;
    if (secondary_head == 0) {
        secondary_head = node;
    } else {
        AnimationManagerNodeOpen* tail = secondary_tail;
        AnimationManagerNodeOpen* next = tail->next;
        if (next != 0) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    secondary_tail = node;
    int id = ++next_id;
    if (id == 0)
        ++next_id;
    object->animation_handle = next_id;
    return AnimationScriptId(next_id);
}
#pragma code_seg()
