// 0x00421B70: publish the selected stage and its resource record.
#include "th10/game/stage_route.hpp"

struct PhaseCursor {
    unsigned char unknown_00[0x3C];
    unsigned int published;                 // +0x3C
    unsigned int selected;                  // +0x40

    __declspec(noinline) void Publish();
};

#pragma code_seg(".text$01publish")
void PhaseCursor::Publish() {
    unsigned int index = selected;
    published = index;
    g_stage_route_current = &g_stage_routes[index];
}
#pragma code_seg()
