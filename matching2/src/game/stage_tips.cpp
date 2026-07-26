#include "th10/game/stage_tips.hpp"

#include <cstring>

// Semantic reconstruction 0x00418D00 - construct a parsed stage-tip entry.
StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip) {
    (void)unused;
    std::memset(tip, 0, sizeof(*tip));
    tip->node.owner = tip;
    tip->duration = 300;
    tip->selection = -1;
    tip->scale = 1.0f;
    tip->state = -1;
    return tip;
}
