// Compiler context only; its bytes are not recovered game code.
#include "../../src/game/title/game_progress_unlock_all_stages_0042c8c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GameProgress_0042c8c0** p, int n) {
    for (int i = 0; i < n; ++i) UnlockAllStages_0042c8c0(p[i]);
    return 0;
}
#pragma code_seg()
