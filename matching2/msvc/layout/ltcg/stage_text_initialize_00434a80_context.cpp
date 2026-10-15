// Compiler context only; never selected as recovered game code.
#include "../../src/game/title/stage_text.cpp"

#pragma code_seg(".text$03context")
int __stdcall StageTextCompilerContext(StageText_00434a80** records, int count,
                                       const StageTextVector_00434a80* local) {
    StageText_00434a80** cursor = records;
    while (count--) {
        StageText_00434a80* record = *cursor++;
        record->Initialize(&record->base_position, local, 4, 0);
    }
    return 0;
}
#pragma code_seg()
