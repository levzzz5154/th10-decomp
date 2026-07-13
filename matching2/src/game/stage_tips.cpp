#include "th10/game/stage_tips.hpp"

extern "C" void* __cdecl memset(void* destination, int value, uint32_t size);

// 0x00418D00 - Construct a parsed stage-tip entry.
StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip) {
    memset(tip, 0, sizeof(StageTip));

    volatile uint32_t* fields = (volatile uint32_t*)tip;
    int32_t value = 0;
    fields[4] = value;
    fields[5] = value;
    fields[3] = (uint32_t)tip;
    --value;
    fields[0x21] = value;
    fields[0x1C] = value;
    fields[0x1B] = 300;
    fields[0x1F] = 0x3F800000;
    return tip;
}
