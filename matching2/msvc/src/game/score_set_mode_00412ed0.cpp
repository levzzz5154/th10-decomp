// 0x00412ED0..0x00412EDF: Score_SetMode
// The score object keeps the selected mode and a cached mode-dependent result
// in adjacent words.  The cache is invalidated only when the selection
// changes.
// The native-LTCG caller establishes the retail internal convention: state
// arrives in EAX and new_mode arrives in ECX.
struct ScoreModeState {
    unsigned char reserved_000[0x44];
    int mode;
    unsigned char reserved_048[4];
    int cached_result;
};
typedef char ScoreModeState_size_must_fit[
    sizeof(ScoreModeState) == 0x50 ? 1 : -1];

#pragma code_seg(".text$01score_mode")
__declspec(noinline) void Score_SetMode(ScoreModeState* state, int new_mode) {
    if (state->mode != new_mode)
        state->cached_result = 0;
    state->mode = new_mode;
}
#pragma code_seg()
