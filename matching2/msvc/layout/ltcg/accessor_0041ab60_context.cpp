// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0041ab60_0041ab60.cpp"
#include "th10/game/entity_movement_slot_0041ab70.hpp"

#pragma code_seg(".text$05context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0041ab60** items,
                                      EntityMovementSlot_0041ab70** slots,
                                      const MovementPair_0041ab70* sources,
                                      const MovementPair_0041ab70* destinations,
                                      int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
        (*slots++)->Initialise(sources++, destinations++, 8, 4);
    }
    return total;
}
#pragma code_seg()
