// 0x004175E0: advance the rank level and publish the resulting rank record.

struct RankTableEntry {
    int values[12];
};

struct RankState {
    char unknown[0x3C];
    int level;

    __declspec(noinline) void AdvanceLevel();
};

extern "C" RankTableEntry g_stage_routes[];
extern "C" RankTableEntry* g_stage_route_current;

#pragma code_seg(".text$01rank")
void RankState::AdvanceLevel() {
    if (this->level < 7)
        this->level = this->level + 1;
    g_stage_route_current = &g_stage_routes[this->level];
}
#pragma code_seg()
