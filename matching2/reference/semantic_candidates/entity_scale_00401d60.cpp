#include "th10/game/entity.hpp"

// Retail 0x00401D60..0x00401D7F takes Entity in EAX and two float values
// on the stack. It sets the scale fields and flag bit 3.
extern "C" void __cdecl SetEntityScale_00401d60(
    Entity* entity, float scale_x, float scale_y) {
    entity->scale_x = scale_x;
    entity->scale_y = scale_y;
    entity->flags_35C |= 8;
}

// Retail 0x00401D80 is a separate, unreferenced one-byte RET.
extern "C" void EmptyReturn_00401d80() {
}
