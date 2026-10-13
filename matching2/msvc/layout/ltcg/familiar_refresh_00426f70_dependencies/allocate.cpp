// Complete 4096-entry pool allocator at 0x00449950, manager ESI and Entity* result EAX.
#include "th10/game/entity.hpp"
#include "../player_initialize_00405860_dependencies/entity_init.cpp"

void* __cdecl operator new(unsigned int size);
Entity* __fastcall Entity_Constructor(Entity* self);

struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};

#pragma code_seg(".text$00449950_allocate")
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
            Entity_Init(created);
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
