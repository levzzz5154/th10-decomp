// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/globals_advance_stage.cpp"

#pragma code_seg(".text$03context")
int __stdcall RankLevelCompilerContext(GlobalsStageView** states, int count) {
    GlobalsStageView** cursor = states;
    while (count--) {
        GlobalsStageView* state = *cursor++;
        state->AdvanceStage();
        state->AdvanceStage();
    }
    return 0;
}
#pragma code_seg()
