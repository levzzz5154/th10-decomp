#pragma once
#include "th10/render/animation_public_callers.hpp"
struct CutAnimationId {
 unsigned int value;
 CutAnimationId() {}
 CutAnimationId(unsigned int id):value(id) {}
 CutAnimationId& operator=(CutAnimationId other) {value=other.value;return *this;}
 CutAnimationId& operator++() {++value;return *this;}
 bool operator==(CutAnimationId other) const {return value==other.value;}
};
struct CutAnimationNode {Entity* object;CutAnimationNode* next;CutAnimationNode* previous;};
struct CutAnimationLists {
 unsigned char reserved_000[0x72dad4];
 CutAnimationNode* head;CutAnimationNode* tail;
 unsigned char reserved_72dadc[0x732454-0x72dadc];
 CutAnimationId next_id;
 __declspec(noinline) CutAnimationId RegisterPrimaryBack(Entity* object);
};
struct CutAnimationResource {
 __declspec(noinline) CutAnimationId CreateOffset(int index,const Vector3* point);
};
