// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ab60.cpp"
#include "th10/game/entity_movement_slot.hpp"

#pragma code_seg(".text$05context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0041ab60** items,
                                      EntityMovementSlot** slots,
                                      const MovementPair* sources,
                                      const MovementPair* destinations,
                                      int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
        (*slots++)->Initialise(sources++, destinations++, 8, 4);
    }
    return total;
}
#pragma code_seg()
