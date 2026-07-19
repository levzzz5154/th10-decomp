// 0x0041AB70 FUN_0041ab70
// Entity movement slot initializer (shared by entity VM opcode 0x3c
// under FUN_0043ee30 and the FUN_00419120 invocations).
//
// See the header for the slot layout and the lazy-init semantics.  The
// readable body mirrors the retail bit-for-bit: inline assignment of
// every slot word, lazy-init on bit-0 of the flags, then re-arm.

#include "th10/game/entity_movement_slot.hpp"

#include <cstdint>


extern uint32_t DAT_00476f78;  // shared script-time scale, by reference

void EntityMovementSlot_Init(void* slot,
                              const float* origin,
                              const float* target,
                              uint32_t source_value,
                              uint8_t mode) {
    if (slot == 0) return;
    uint8_t* bytes = static_cast<uint8_t*>(slot);

    *reinterpret_cast<uint32_t*>(bytes + 0x1b4) = source_value;
    *reinterpret_cast<uint32_t*>(bytes + 0x1b8) =
        static_cast<uint32_t>(mode);
    *reinterpret_cast<uint32_t*>(bytes + 0x180) =
        *reinterpret_cast<const uint32_t*>(target);
    *reinterpret_cast<uint32_t*>(bytes + 0x184) =
        *(reinterpret_cast<const uint32_t*>(target) + 1);
    *reinterpret_cast<uint32_t*>(bytes + 0x188) =
        *reinterpret_cast<const uint32_t*>(origin);
    *reinterpret_cast<uint32_t*>(bytes + 0x18c) =
        *(reinterpret_cast<const uint32_t*>(origin) + 1);

    uint32_t* flags = reinterpret_cast<uint32_t*>(bytes + 0x1b0);
    if ((*flags & 1u) == 0) {
        *reinterpret_cast<int32_t*>(bytes + 0x1a4) = 0;
        *reinterpret_cast<int32_t*>(bytes + 0x1a0) =
            static_cast<int32_t>(0xfff0bdc1);
        *reinterpret_cast<int32_t*>(bytes + 0x1a8) = 0;
        // Retail stores a 32-bit address of DAT_00476f78; on a 64-bit
        // host that 32-bit pointer would not fit in a real pointer, so
        // mirror the retail 4-byte write by truncating to uint32_t.
        *reinterpret_cast<uint32_t*>(bytes + 0x1ac) =
            static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(&DAT_00476f78));
        *flags |= 1u;
    }
    *reinterpret_cast<int32_t*>(bytes + 0x1a4) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x1a8) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x1a0) =
        static_cast<int32_t>(0xffffffff);
}