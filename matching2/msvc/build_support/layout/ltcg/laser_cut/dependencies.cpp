// Complete registrar and allocator bodies. Entity initialization is the
// actual representable ECX-dummy/EDX-object fastcall boundary from entity.hpp.
#include "th10/render/animation_public_callers.hpp"
#include <string.h>
#include "animation_ids.hpp"
struct AnmListNode_00448d50 {
    void* owner;
    AnmListNode_00448d50* next;
    AnmListNode_00448d50* previous;
};

#pragma code_seg(".text$f004489d0F")
CutAnimationId CutAnimationLists::RegisterPrimaryBack(Entity* object) {
 CutAnimationNode* node=reinterpret_cast<CutAnimationNode*>(&object->manager_node_animation);
 node->object=object;node->next=0;node->previous=0;
 if (!head) head=node;
 else {CutAnimationNode* last=tail;CutAnimationNode* next=last->next;
  if (next) {node->next=next;last->next->previous=node;}
  last->next=node;node->previous=last;
 }
 tail=node;++next_id;
 if (next_id==CutAnimationId(0)) ++next_id;
 object->animation_handle=next_id.value;
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
