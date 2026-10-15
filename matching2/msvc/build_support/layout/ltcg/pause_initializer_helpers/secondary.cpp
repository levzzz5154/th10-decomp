#include "th10/game/pause_initializer_00422ab0.hpp"
#pragma code_seg(".text$11secondary")
Handle4* AnimationSecondaryLists::RegisterSecondaryBack(Handle4* out, Entity* object) {
    AnimationSecondaryNode* node = reinterpret_cast<AnimationSecondaryNode*>(&object->manager_node_animation);
    node->object = object; node->next = 0; node->previous = 0;
    if (head == 0) head = node;
    else {
        AnimationSecondaryNode* old_tail = tail;
        if (old_tail->next != 0) {
            node->next = old_tail->next;
            old_tail->next->previous = node;
        }
        old_tail->next = node; node->previous = old_tail;
    }
    tail = node;
    ++next_handle; if (next_handle == 0) ++next_handle;
    object->animation_handle = next_handle;
    out->value = next_handle;
    return out;
}
#pragma code_seg()
