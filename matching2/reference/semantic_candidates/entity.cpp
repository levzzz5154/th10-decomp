// Readable models removed from matching2/msvc/src/game/entity.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include <string.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/entity.hpp"

// 0x00405D00..0x00405DD6: reset one 0x7F0-byte runtime object.
// The retail entry takes its object in ECX, returns that same pointer in EAX,
// and uses a plain RET.  A single-argument fastcall expresses that ABI.
// Keep the bytes opaque here: this reset reaches beyond the 0x3AC-byte Entity
// base into the owning runtime object's flags.
extern "C" unsigned char* __fastcall Entity_ResetRuntimeState_00405D00(
    unsigned char* entity) {
    const unsigned int clear_registration_bit = 0xFFFFFFFEu;

    // Retail performs these nine clears first.  The following zero-fill
    // supersedes them, but retaining the sequence documents the observed
    // machine-code effects and their order.
    *(unsigned int*)(entity + 0x074) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x0B8) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x104) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x130) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x17C) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x1B8) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x204) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x230) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x380) &= clear_registration_bit;

    memset(entity + 8, 0, 0x3AC);
    *(unsigned short*)(entity + 0x38C) = 0xFFFF;

    *(unsigned int*)(entity + 0x408) &= clear_registration_bit;
    *(unsigned int*)(entity + 0x41C) &= clear_registration_bit;
    for (unsigned int slot = 0; slot != 9; ++slot)
        *(unsigned int*)(entity + 0x624 + slot * 0x34) &=
            clear_registration_bit;

    return entity;
}
