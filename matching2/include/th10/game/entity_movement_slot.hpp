// 0x0041AB70 FUN_0041ab70
// Entity movement slot initializer (shared by entity VM opcode 0x3c
// under FUN_0043ee30 and the FUN_00419120 invocations).
//
// Retail signature:
//   void __fastcall FUN_0041ab70(float* origin, float* target,
//                                uint32_t source_value, uint8_t mode);
// with the owner pointer (the entity movement slot) passed implicitly
// via the EAX register (a __thiscall-style convention that Ghidra surfaces
// as ``in_EAX``).
//
// The slot layout (offsets relative to EAX):
//   0x180/0x184 : target float pair (from param_2[0..1])
//   0x188/0x18c : origin float pair (from param_1[0..1])
//   0x1a0       : state word (init 0xfff0bdc1 on first call, then 0xffffffff)
//   0x1a4       : counter word (always reset to 0 on every call)
//   0x1a8       : second counter word (always reset to 0 on every call)
//   0x1ac       : pointer to the global script-time scale DAT_00476f78
//   0x1b0       : flags word (bit 0 marks the record as initialized)
//   0x1b4       : the source value (param_3, a 4-byte payload)
//   0x1b8       : the mode byte (param_4, zero-extended to 32 bits)
//
// The (state, counter, second_counter, time_scale_ptr, flags) layout at
// +0x1a0..+0x1b0 mirrors the per-axis movement record used by the ECL
// VM dispatcher's helper ECL_InitMovementRecord; this is the variant
// slot bound to the entity runtime.

#ifndef TH10_GAME_ENTITY_MOVEMENT_SLOT_HPP
#define TH10_GAME_ENTITY_MOVEMENT_SLOT_HPP

#include <cstdint>

// Initialize (or re-arm) the entity movement slot at ``slot`` using the
// origin/target float pairs and the source value / mode byte operands.
//
// The first call lazy-initializes the record's state word and stores the
// pointer to the shared script-time scale; every call (including the
// first) re-arms the state to the runtime "active" encoding.
void EntityMovementSlot_Init(void* slot,
                              const float* origin,
                              const float* target,
                              uint32_t source_value,
                              uint8_t mode);

#endif  // TH10_GAME_ENTITY_MOVEMENT_SLOT_HPP