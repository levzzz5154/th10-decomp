// 0x00442050 FUN_00442050
// Readable reconstruction of retail helper FUN_00442050.
//
// FUN_00442050 is the per-slot color animation initializer invoked by
// entity VM opcode 0x4e under FUN_0043ee30.  It mirrors the
// FUN_0041ab70 movement-slot initializer but operates on 3-byte color
// triples instead of 2-float pairs.
//
// The slot layout (offsets relative to ``slot``):
//   0x1bc/0x1c0/0x1c4 : target color bytes param_2[0..2] (each zero-extended
//                        to a 32-bit word)
//   0x1c8/0x1cc/0x1d0 : origin color bytes param_1[0..2] (same encoding)
//   0x1d4..0x1e8      : 24 bytes zeroed
//   0x1ec             : state word (init 0xfff0bdc1 first call, 0xffffffff after)
//   0x1f0             : counter word (always reset to 0)
//   0x1f4             : second counter word (always reset to 0)
//   0x1f8             : pointer to the shared script-time scale DAT_00476f78
//   0x1fc             : flags word (bit 0 marks the record as initialized)
//   0x200             : the source value (param_3, a 4-byte payload)
//   0x204             : the mode byte (param_4, zero-extended to 32 bits)
//
// The (state, counter, second_counter, time_scale_ptr, flags) layout at
// +0x1ec..+0x1fc mirrors FUN_0041ab70's record block shifted by 0x4c.

#ifndef TH10_GAME_ENTITY_COLOR_SLOT_HPP
#define TH10_GAME_ENTITY_COLOR_SLOT_HPP

#include <cstdint>

// Initialize (or re-arm) the entity color slot at ``slot`` using the
// 3-byte origin/target color pairs and the source value / mode byte
// operands.  First call lazy-initializes the state word and stores the
// script-time-scale pointer; every call re-arms the state to the
// runtime "active" encoding.
void EntityColorSlot_Init(void* slot,
                          const uint8_t* origin_color,
                          const uint8_t* target_color,
                          uint32_t source_value,
                          uint8_t mode);

#endif  // TH10_GAME_ENTITY_COLOR_SLOT_HPP