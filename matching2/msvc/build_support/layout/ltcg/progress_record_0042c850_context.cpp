// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/progress.cpp"

#pragma code_seg(".text$03context")
int __stdcall ProgressRecordCompilerContext(GameProgress2** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->HasAnyPlayRecord();
    }
    return total;
}
#pragma code_seg()
