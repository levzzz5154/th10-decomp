// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bullet/bullet_slot_construct_00405d00.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
BulletSlot_00405d00* __stdcall BulletSlotConstructCompilerContext(BulletSlot_00405d00* slots, int count) {
    for (int i = 0; i < count; ++i)
        new (&slots[i]) BulletSlot_00405d00;
    return slots;
}
#pragma code_seg()
