#pragma once

#include <cstdint>

// Sizes (in 32-bit words) of the retail manager blocks reset by the
// recovered constructors below.
constexpr uint32_t kEffectManagerDwords = 0x2E21;   // 0xB884 bytes
constexpr uint32_t kProgressManagerDwords = 0x16B3; // 0x5ACC bytes
constexpr uint32_t kEntityBlockPoolDwords = 0x27B4; // 0x9ED0 bytes

// 0x0042B430 - Reset the 0xB884-byte effect manager: clear the whole
// block, set constructed bit 1 in the leading flags word, and publish
// the instance through the retail global at 0x00477840.
void EffectManager_ResetAndPublish(uint32_t* state);

// 0x0042C920 - Construct the 0x5ACC-byte progress manager: clear the
// whole block, set bit 1 in the flags word at +0x04, and publish the
// instance through the retail global at 0x0047784C.
uint32_t* ProgressManager_ConstructAndPublish(uint32_t* state);

// 0x00413810 - Construct the 0x9ED0-byte entity block pool: run the
// entity constructor over the six embedded entity arrays (10 + 10 + 9 +
// 4 + 2 + 7 elements of 0x3AC bytes), clear the whole block, set bit 1
// in the leading flags word, and publish the instance through the
// retail global at 0x0047770C. The vector-constructor iterator is
// injected as a per-element callback.
uint32_t* EntityBlockPool_ConstructAndPublish(uint32_t* state,
                                              void (*construct_entity)(void*));
