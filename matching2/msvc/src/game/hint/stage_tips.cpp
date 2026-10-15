#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/stage_tips.hpp"

extern "C" void* __cdecl memset(void* destination, int value,
                                  unsigned int size);

// 0x00418D00..0x00418D32: initialize one parsed stage-tip record.
StageTip* __fastcall StageTip_Initialize(void*, StageTip* tip) {
    memset(tip, 0, sizeof(*tip));
    tip->node.Initialize(tip);
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;
    return tip;
}
