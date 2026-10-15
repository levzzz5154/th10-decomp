// 0x00413810: construct the HUD. The six sprite pools, the lone
// sprite and the frame timer are built as members, then the whole block is
// cleared, marked and published. The compiler-generated cleanups at
// 0x00465430..0x0046549A destroy the pools already built if a later one
// throws.
#include "th10/game/hud_construct.hpp"

#pragma code_seg(".text$01construct")
Hud::Hud() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_0047770c = this;
}
#pragma code_seg()
