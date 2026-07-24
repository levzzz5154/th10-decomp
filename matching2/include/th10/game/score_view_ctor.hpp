#pragma once

#include <cstdint>

// Vtable image installed by the constructor tail (retail 0x0046DA10;
// the host test provides the symbol).
extern const void* PTR_LAB_0046da10;

// 0x0041C680 - Score-view constructor tail: run the injected base
// constructor (retail 0x0041C030), install the vtable pointer, clear
// the 0x7E-word header block at word 0x109, seed the 8.0f default at
// word 0x114, and wipe the two embedded 0xEB-word entity slots at words
// 0x187 and 0x272, terminating each with a 0xFFFF half-word (words
// 0x268 and 0x353). The retail timer-flag bit clears inside those
// ranges are dead stores and are documented in the source. The state is
// treated as raw 32-bit words; the vtable pointer keeps the retail
// 32-bit truncation semantics on the host.
void ScoreView_ConstructTail(uint32_t* state, void (*construct_base)(uint32_t*));
