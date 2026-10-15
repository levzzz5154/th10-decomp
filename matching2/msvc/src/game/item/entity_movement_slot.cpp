#include "th10/game/entity_movement_slot_0041ab70.hpp"

// 0x0041AB70..0x0041ABF7: initialise one entity movement slot.
#pragma code_seg(".text$03movement")
void EntityMovementSlot::Initialise(
        const MovementPair* source_value,
        const MovementPair* destination_value,
        int mode_value, unsigned char interpolation_value) {
    mode = mode_value;
    interpolation = interpolation_value;
    source = *source_value;
    destination = *destination_value;
    if (!(flags & 1)) {
        previous = 0;
        timer = -999999;
        elapsed = 0;
        speed = (const float*)0x00476F78;
        flags |= 1;
    }
    previous = 0;
    elapsed = 0;
    timer = -1;
}
#pragma code_seg()
