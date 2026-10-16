// Compiler context only; its bytes are not recovered game code.
#include "../../../src/game/title/game_progress_unlock_all_stages.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GameProgress3** p, int n) {
    for (int i = 0; i < n; ++i) UnlockAllStages2(p[i]);
    return 0;
}
#pragma code_seg()
