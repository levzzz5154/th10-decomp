#pragma once

#include <cstdint>

constexpr uint32_t kPlayerBlockDwords = 0x111E;  // 0x4478 bytes

// 0x004246C0 - Reset the 0x4478-byte player block and publish it
// through the retail global at 0x00477834. The long retail prologue
// (timer in-use bit clears, two embedded 0x3AC-byte entity wipes with
// 0xFFFF terminators, the 0x80 watch slots at word 0x12B with a
// 0x17-word stride, and the 0x21 indicator slots at word 0xD58 with a
// 0x1B-word stride) consists entirely of dead stores: the function ends
// by zeroing the whole block before publishing.
void Player_ResetAndPublish(uint32_t* state);
