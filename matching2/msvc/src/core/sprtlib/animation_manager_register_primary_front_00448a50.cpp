// Prepend an animation to the primary list and assign its nonzero ID.
#include "th10/game/player_hud_animations.hpp"
// Entity's embedded manager links: owner, next and previous.
struct AnimationEntityLinkView {
    int animation_handle;
    Entity* manager_links[3];
};
typedef char ManagerLinksOffset[offsetof(AnimationEntityLinkView, manager_links) == 4 ? 1 : -1];

#pragma code_seg(".text$00448a50_fn")
AnimationRef AnimationLists::RegisterPrimaryFront(Entity* object) {
    AnimationListNode* node = reinterpret_cast<AnimationListNode*>(&object->manager_node_animation);
    Entity** links = reinterpret_cast<AnimationEntityLinkView*>(object)->manager_links;
    links[0] = object;
    links[1] = 0;
    links[2] = 0;
    if (!primary_head)
        primary_tail = node;
    else {
        AnimationListNode* head = primary_head;
        AnimationListNode* next = node->next;
        if (next) {
            head->next = next;
            node->next->previous = head;
        }
        node->next = head;
        head->previous = node;
    }
    primary_head = node;
    ++next_id;
    if (next_id == 0) ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
