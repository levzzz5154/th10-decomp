// 0x00442050 FUN_00442050
// Readable reconstruction of retail helper FUN_00442050.
//
// See the header for the slot layout and lazy-init semantics.

#include "th10/game/entity_color_slot.hpp"

#include <cstdint>


extern uint32_t DAT_00476f78;  // shared script-time scale, by reference

void EntityColorSlot_Init(void* slot,
                          const uint8_t* origin_color,
                          const uint8_t* target_color,
                          uint32_t source_value,
                          uint8_t mode) {
    if (slot == 0) return;
    uint8_t* bytes = static_cast<uint8_t*>(slot);

    *reinterpret_cast<uint32_t*>(bytes + 0x200) = source_value;
    *reinterpret_cast<uint32_t*>(bytes + 0x1d4) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x1d8) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x1dc) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x1e0) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x1e4) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x1e8) = 0;
    *reinterpret_cast<uint32_t*>(bytes + 0x204) =
        static_cast<uint32_t>(mode);

    // 3 target bytes at 0x1bc..0x1c4, 3 origin bytes at 0x1c8..0x1d0.
    // Each byte is zero-extended to a 32-bit word by the retail.
    *reinterpret_cast<uint32_t*>(bytes + 0x1bc) =
        static_cast<uint32_t>(target_color[0]);
    *reinterpret_cast<uint32_t*>(bytes + 0x1c0) =
        static_cast<uint32_t>(target_color[1]);
    *reinterpret_cast<uint32_t*>(bytes + 0x1c4) =
        static_cast<uint32_t>(target_color[2]);
    *reinterpret_cast<uint32_t*>(bytes + 0x1c8) =
        static_cast<uint32_t>(origin_color[0]);
    *reinterpret_cast<uint32_t*>(bytes + 0x1cc) =
        static_cast<uint32_t>(origin_color[1]);
    *reinterpret_cast<uint32_t*>(bytes + 0x1d0) =
        static_cast<uint32_t>(origin_color[2]);

    uint32_t* flags = reinterpret_cast<uint32_t*>(bytes + 0x1fc);
    if ((*flags & 1u) == 0) {
        *reinterpret_cast<int32_t*>(bytes + 0x1f0) = 0;
        *reinterpret_cast<int32_t*>(bytes + 0x1ec) =
            static_cast<int32_t>(0xfff0bdc1);
        *reinterpret_cast<int32_t*>(bytes + 0x1f4) = 0;
        // Retail stores a 32-bit address of DAT_00476f78; on a 64-bit
        // host the full pointer would overflow into the flags word at
        // +0x1fc, so mirror the 4-byte retail write by truncating.
        *reinterpret_cast<uint32_t*>(bytes + 0x1f8) =
            static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(&DAT_00476f78));
        *flags |= 1u;
    }
    *reinterpret_cast<int32_t*>(bytes + 0x1f0) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x1f4) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x1ec) =
        static_cast<int32_t>(0xffffffff);
}