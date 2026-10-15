// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/stage_text.cpp"

#pragma code_seg(".text$03context")
int __stdcall StageTextCompilerContext(StageText** records, int count,
                                       const StageTextVector* local) {
    StageText** cursor = records;
    while (count--) {
        StageText* record = *cursor++;
        record->Initialize(&record->base_position, local, 4, 0);
    }
    return 0;
}
#pragma code_seg()
