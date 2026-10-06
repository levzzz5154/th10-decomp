// Complete registrar and allocator bodies. Entity initialization is the
// actual representable ECX-dummy/EDX-object fastcall boundary from entity.hpp.
#include "th10/render/animation_public_callers.hpp"
#include <string.h>
struct AnmListNode_00448d50 {
    void* owner;
    AnmListNode_00448d50* next;
    AnmListNode_00448d50* previous;
};

#pragma code_seg(".text$f004489d0F")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    void** node = (void**)(e + 0x04);
    node[0] = e; node[1] = 0; node[2] = 0;
    void* head = *(void**)(m + 0x72DAD4);
    if (head == 0) { *(void**)(m + 0x72DAD4) = node; }
    else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        unsigned char* next = *(unsigned char**)(tail + 0x04);
        if (next != 0) { node[1] = next; *(unsigned char**)(next + 0x08) = (unsigned char*)node; }
        *(unsigned char**)(tail + 0x04) = (unsigned char*)node;
        node[2] = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    int id = ++*(int*)(m + 0x732454);
    if (id == 0) { id = ++*(int*)(m + 0x732454); }
    // Keep the actual two counter reads around the entity/out writes.
    // The final read clobbers EDX, as the retail registrar does.
    *(int*)(e + 0x00) = *(int*)(m + 0x732454);
    memcpy(out, m + 0x732454, sizeof(*out));
    return out;
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
