// Complete registrar and allocator bodies with the genuine one-pointer
// entity initializer visible in this graph.
#include "animation_public_callers.hpp"
#include <string.h>
#include "registration.hpp"
#pragma code_seg(".text$f004489d0F")
AnimationRef AnimationLists::RegisterPrimaryBack(Entity* object) {
    AnimationListNode* node = reinterpret_cast<AnimationListNode*>(
        &object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        AnimationListNode* tail = primary_tail;
        AnimationListNode* next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    ++next_id;
    if (next_id == 0) ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()

void* __cdecl operator new(unsigned int size);
Entity* __fastcall Entity_Constructor(Entity* self);

#pragma code_seg(".text$f00449950F")
Entity* AnimationPool::Allocate() {
    int slot = next_slot;
    Entity* object = &objects[slot];
    if (occupied[slot]) {
        slot = (slot + 1) % 4096;
        next_slot = slot;
        object = &objects[slot];
        if (occupied[slot]) {
            Entity* block = (Entity*)operator new(sizeof(Entity));
            Entity* created = block != 0 ? Entity_Constructor(block) : (Entity*)0;
            object = created;
            Entity_Init(0, created);
        } else {
            occupied[slot] = 1;
        }
    } else {
        occupied[slot] = 1;
    }
    next_slot = (next_slot + 1) % 4096;
    return object;
}
#pragma code_seg()
