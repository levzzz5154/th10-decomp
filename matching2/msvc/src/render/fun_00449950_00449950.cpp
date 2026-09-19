// 0x00449950..0x004499F0 (161 bytes): AnimationPool::Allocate - the animation
// manager's object-pool allocator.  Every create family in the manager
// (0x00448D00/0x00448E30/0x00448F60/0x00449090, 0x00448D50/0x00448E80/
// 0x00448FB0/0x004490E0, 0x00448DB0/0x00448EE0/0x00449010/0x00449140) reaches
// it as `mov esi,[data_00491C10]; call 0x449950`, i.e. the manager arrives in
// ESI and the result in EAX.
//
// The manager owns a 0x1000-entry ring of Entity-sized (0x3AC) slots at +0x68,
// a per-slot busy byte array at +0x3AC068 and the ring cursor at +0x3AD068.
// Allocate starts at the cursor: a free slot is marked busy and handed out; a
// busy slot advances the cursor once, and only if the successor is busy too is
// a fresh 0x3AC-byte object taken from the heap and run through the landed
// Entity_Constructor (0x00402050) and Entity_Init (0x00401DE0).  Either way the
// tail advances the cursor past the returned slot, so the ring rotates.
//
// Retail's modulo is the signed `% 4096` shape (inc/and 0x80000FFF/jns/dec/or
// 0xFFFFF000/inc); the cursor is re-read from the manager in the tail, which is
// why the source stores `slot` back before the second probe and re-reads
// `next_slot` at the end rather than reusing the local.
//
// The heap path keeps two variables: the constructed object in `block`'s
// ternary result (`created`) and the value returned through `object`.  Retail
// emits `mov edx,eax / mov edi,eax` - the initializer's argument and the
// result home both copied out of the object's production register - and only
// the separate temporary reproduces that; assigning straight into `object` and
// passing `object` makes the backend copy the argument out of the home
// register instead (`mov edi,eax / mov edx,edi`, two bytes short).
//
// The manager's registers are not expressible in a plain translation unit, so
// the body is compiled in the native-LTCG cluster
// layout/ltcg/anim_pool_alloc_00449950.json, whose driver also carries the
// compiled ABI anchor for the Entity_Init call.
#include "th10/game/entity.hpp"

void* __cdecl operator new(unsigned int size);
Entity* __fastcall Entity_Constructor(Entity* self);

struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};

#pragma code_seg(".text$03allocate")
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
