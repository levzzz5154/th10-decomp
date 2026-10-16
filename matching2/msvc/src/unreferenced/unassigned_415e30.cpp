// 0x00415E30..0x00415E8C: TickRecoveryState
//
// This guarded script-state tick first asks 0x00415E90 whether to stop. If it
// keeps running, it copies the current frame counter to the previous counter
// and advances the timer using the shared speed pointer. At normal speed it
// advances by one frame; otherwise it truncates the accumulated elapsed time.
// Native LTCG assigns the state to ESI and emits plain RET, as in retail.

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

extern "C" int __stdcall asm_FUN_00415e90_00415e90(void* state);

struct RecoveryTickState {
    int pad_00;             // +0x00
    int previous;           // +0x04
    int current;            // +0x08
    float elapsed;          // +0x0C
    const float* speed;     // +0x10
};

#pragma code_seg(".text$01tick")
__declspec(noinline) int __stdcall TickRecoveryState(RecoveryTickState* state) {
    if (asm_FUN_00415e90_00415e90(state))
        return 1;

    state->previous = state->current;
    if (*state->speed > g_frame_timer_normal_lower &&
        *state->speed < g_frame_timer_normal_upper) {
        ++state->current;
        state->elapsed += 1.0f;
    } else {
        state->current = int(state->elapsed += *state->speed);
    }
    return 0;
}
#pragma code_seg()
