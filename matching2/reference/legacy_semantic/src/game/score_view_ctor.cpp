#include "th10/game/score_view_ctor.hpp"

#include <cstring>

// 0x0041C680 - Score-view constructor tail. Retail order: base
// constructor (0x0041C030), vtable install, zero words 0x109..0x186,
// store 8.0f at word 0x114, clear the in-use bit of nine embedded timer
// flag words (0x1A2..0x265 -- all dead, the following wipe covers
// them), zero the first entity slot (words 0x187..0x271) and write the
// 0xFFFF terminator half-word at word 0x268, clear eight more timer
// flag words (0x28D..0x350, equally dead), and zero the second entity
// slot (words 0x272..0x35C) with its terminator at word 0x353.
void ScoreView_ConstructTail(uint32_t* state,
                             void (*construct_base)(uint32_t*)) {
    if (construct_base != 0) {
        construct_base(state);
    }
    state[0] = (uint32_t)(uintptr_t)&PTR_LAB_0046da10;

    memset(state + 0x109, 0, 0x7E * sizeof(uint32_t));
    state[0x114] = 0x41000000u;  // 8.0f image

    // Nine timer-flag bit clears at words 0x1A2..0x265: dead, wiped by
    // the next block.
    memset(state + 0x187, 0, 0xEB * sizeof(uint32_t));
    state[0x268] = 0xFFFFu;  // half-word terminator over zeroed word

    // Eight timer-flag bit clears at words 0x28D..0x350: dead, wiped by
    // the next block.
    memset(state + 0x272, 0, 0xEB * sizeof(uint32_t));
    state[0x353] = 0xFFFFu;  // half-word terminator over zeroed word
}
