// Compiler context only; never selected as recovered game code.
#include "../../../src/game/laser/laser_mark_eligible.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScoreRecordsMarkEligibleCompilerContext(
        LaserListView** records, int count) {
    int marked = 0;
    while (count--) {
        marked += (*records++)->MarkEligible();
    }
    return marked;
}
#pragma code_seg()
