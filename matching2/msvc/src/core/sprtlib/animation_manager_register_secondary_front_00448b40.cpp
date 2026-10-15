// Prepend an animation to the secondary list and assign its nonzero ID.
#include "th10/game/card_animations.hpp"
// Entity's embedded manager links: owner, next and previous.
struct AnimationEntityLinkView {
    int animation_handle;
    Entity* manager_links[3];
};
typedef char ManagerLinksOffset[offsetof(AnimationEntityLinkView, manager_links) == 4 ? 1 : -1];

#pragma code_seg(".text$00448b40_fn")
AnimationRef AnimationLists::RegisterSecondaryFront(Entity* object) {
    AnimationListNode* node = reinterpret_cast<AnimationListNode*>(&object->manager_node_animation);
    Entity** links = reinterpret_cast<AnimationEntityLinkView*>(object)->manager_links;
    links[0] = object;
    links[1] = 0;
    links[2] = 0;
    if (!secondary_head)
        secondary_tail = node;
    else {
        AnimationListNode* head = secondary_head;
        AnimationListNode* next = node->next;
        if (next) {
            head->next = next;
            node->next->previous = head;
        }
        node->next = head;
        head->previous = node;
    }
    secondary_head = node;
    ++next_id;
    if (next_id == 0) ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
