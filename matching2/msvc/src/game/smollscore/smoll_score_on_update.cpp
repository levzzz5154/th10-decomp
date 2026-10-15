// 0x0042B9A0: the score popups' update task (registered by 0x0042B4D0).
#include "th10/game/smoll_score_view.hpp"

#pragma code_seg(".text$02wrapper")
int SmollScoreView::Update() {
    return UpdatePopups();
}
#pragma code_seg()
