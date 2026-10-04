#pragma once
// The animation manager as the side panel's routines use it: the object pool,
// the primary list and the id lookup.
#include <stddef.h>
#include "th10/game/entity.hpp"

struct AnimationRef {
    unsigned int value;
    AnimationRef() {}
    AnimationRef(unsigned int value_) : value(value_) {}
    AnimationRef& operator++() { ++value; return *this; }
    bool operator==(AnimationRef other) const { return value == other.value; }
};

struct AnimationListNode {
    Entity* object;
    AnimationListNode* next;
    AnimationListNode* previous;
};

struct AnimationPool {
    Entity* Allocate();                            // 0x00449950
};

struct AnimationResource_00449870 {
    void InitializeObject(Entity* object, int index); // 0x00449870
};

struct AnimationLists {
    unsigned char reserved_000000[0x72DAD4];
    AnimationListNode* primary_head;               // +0x72DAD4
    AnimationListNode* primary_tail;               // +0x72DAD8
    AnimationListNode* secondary_head;             // +0x72DADC
    AnimationListNode* secondary_tail;             // +0x72DAE0
    unsigned char reserved_72dae4[0x732454 - 0x72DAE4];
    AnimationRef next_id;                          // +0x732454

    AnimationRef RegisterPrimaryBack(Entity* object); // 0x004489D0

    // The lookup at 0x004491C0, expanded in place.
    __forceinline Entity* FindInline(int id) {
        if (id == 0)
            return 0;
        AnimationListNode* node;
        for (node = primary_head; node != 0; node = node->next)
            if (node->object->animation_handle == id)
                return node->object;
        for (node = secondary_head; node != 0; node = node->next)
            if (node->object->animation_handle == id)
                return node->object;
        return 0;
    }
};

typedef char AnimationLists_next_id[offsetof(AnimationLists, next_id) == 0x732454 ? 1 : -1];
