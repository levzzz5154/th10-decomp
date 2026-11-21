// 0x004175E0: advance the rank level and publish the resulting rank record.

#include "th10/game/stage_route.hpp"

struct GlobalsStageView {
    char unknown[0x3C];
    int level;

    __declspec(noinline) void AdvanceStage();
};

#pragma code_seg(".text$01rank")
void GlobalsStageView::AdvanceStage() {
    if (this->level < ExtraStageIndex)
        this->level = this->level + 1;
    g_stage_route_current = &g_stage_routes[this->level];
}
#pragma code_seg()
