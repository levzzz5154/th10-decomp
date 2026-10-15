// 0x00421F60 (28 bytes): snapshot the current frame value and update the
// largest frame value seen by the game state.

extern "C" int g_globals;
extern "C" int g_globals_score;

struct GameStateFrameState {
    unsigned char unknown_0000[0x9E78];
    int frame_value;
};

typedef char GameStateFrameState_size_must_fit[
    sizeof(GameStateFrameState) == 0x9E7C ? 1 : -1];

#pragma code_seg(".text$01maximum")
__declspec(noinline) int GameState_UpdateFrameMaximum(GameStateFrameState* state) {
    state->frame_value = g_globals_score;
    if (g_globals < state->frame_value)
        g_globals = state->frame_value;
    return state->frame_value;
}
#pragma code_seg()
