#pragma once
#include "th10/game/entity.hpp"
#include <stddef.h>
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

struct AnimationLists {
    unsigned char reserved_000000[0x72DAD4];
    AnimationListNode* primary_head;               // +0x72DAD4
    AnimationListNode* primary_tail;               // +0x72DAD8
    AnimationListNode* secondary_head;             // +0x72DADC
    AnimationListNode* secondary_tail;             // +0x72DAE0
    unsigned char reserved_72dae4[0x732454 - 0x72DAE4];
    AnimationRef next_id;                          // +0x732454

    AnimationRef RegisterPrimaryBack(Entity* object); // 0x004489D0
};
typedef char RegistrationCounterOffset[offsetof(AnimationLists,next_id)==0x732454?1:-1];
