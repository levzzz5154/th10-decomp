// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/front_sync_high_score.cpp"

extern "C" FrontScoreState* g_card;

#pragma code_seg(".text$03context")
int __stdcall GameStateFrameMaximumCompilerContext(int count) {
    int total = 0;
    while (count--)
        total += Front_SyncHighScore(g_card);
    return total;
}
#pragma code_seg()
