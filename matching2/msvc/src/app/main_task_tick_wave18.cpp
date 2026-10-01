#include "th10/platform/sound_fade_manager_wave18.hpp"
#pragma code_seg(".text$00b2_main")
__declspec(noinline) int __fastcall MainTaskTickWave18(MainTaskStateWave18* state) {
    if ((state->flags_3CC & 0x80) != 0 && state->state_63C == 0)
        data_00491fb8 = 3;
    data_00492590.TickFades();
    PollInputWave18(0);
    if (AnmPendingWave18(data_00491c10)) return 4;
    int request = state->request_648;
    if (request) {
        // Retail encodes the two statuses as a mask: request 2 returns 4,
        // while every other nonzero request returns 1.
        int other_request = request != 2;
        return ((other_request - 1) & 3) + 1;
    }
    int result = state->UpdateMode();
    if (result == 1) return 1;
    return result;
}
#pragma code_seg()

// The complete real private mode callee is retained without recovery credit.
#include "../../layout/ltcg/sound_fade_wave18_mode.cpp"
