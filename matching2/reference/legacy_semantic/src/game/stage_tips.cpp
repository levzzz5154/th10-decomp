#include "th10/game/stage_tips.hpp"

#include <cstring>

// 0x00418D00 - construct a parsed stage-tip entry. The two explicit node
// zero-stores after memset are compiler-visible in the retail body and keep
// the function extent at 51 bytes; omitting them produces a 45-byte build.
StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip) {
    (void)unused;
    std::memset(tip, 0, sizeof(*tip));
    tip->node.next = 0;
    tip->node.previous = 0;
    tip->node.owner = tip;
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;
    return tip;
}
