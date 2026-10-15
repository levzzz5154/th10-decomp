// 0x00408910: construct the spell-card manager (Card, card.cpp). The three sprite pools and the
// frame timer are built as members, then the whole block is cleared, marked
// and published. The compiler-generated cleanups at 0x004654E0 and
// 0x004654F9 destroy the pools already built if a later one throws.
#include "th10/game/card.hpp"

#pragma code_seg(".text$01construct")
Card::Card() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_card = this;
}
#pragma code_seg()
