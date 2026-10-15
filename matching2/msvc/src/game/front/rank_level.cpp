// 0x004175E0: advance the rank level and publish the resulting rank record.

struct RankTableEntry {
    int values[12];
};

struct RankState {
    char unknown[0x3C];
    int level;

    __declspec(noinline) void AdvanceLevel();
};

extern "C" RankTableEntry data_00474788[];
extern "C" RankTableEntry* data_00477848;

#pragma code_seg(".text$01rank")
void RankState::AdvanceLevel() {
    if (this->level < 7)
        this->level = this->level + 1;
    data_00477848 = &data_00474788[this->level];
}
#pragma code_seg()
