// Compiler context only; never selected as recovered game code.
#include "../../../../src/game/bullet/bullet_slot_construct.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
BulletSlot2* __stdcall BulletSlotConstructCompilerContext(BulletSlot2* slots, int count) {
    for (int i = 0; i < count; ++i)
        new (&slots[i]) BulletSlot2;
    return slots;
}
#pragma code_seg()
