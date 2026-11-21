// 0x00421F60 (28 bytes): snapshot the current frame value and update the
// largest frame value seen by the game state.

extern "C" int g_globals;
extern "C" int g_globals_score;

struct FrontScoreState {
    unsigned char unknown_0000[0x9E78];
    int displayed_score;
};

typedef char GameStateFrameState_size_must_fit[
    sizeof(FrontScoreState) == 0x9E7C ? 1 : -1];

#pragma code_seg(".text$01maximum")
__declspec(noinline) int Front_SyncHighScore(FrontScoreState* state) {
    state->displayed_score = g_globals_score;
    if (g_globals < state->displayed_score)
        g_globals = state->displayed_score;
    return state->displayed_score;
}
#pragma code_seg()
