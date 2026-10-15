// 0x0042B430: the score popups' (SmollScore) constructor, shared with SmollScore_Create.
#include "th10/game/smoll_score.hpp"

#pragma code_seg(".text$00nctor")
__declspec(noinline) SmollScore::SmollScore() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_smoll_score = this;
}
#pragma code_seg()
