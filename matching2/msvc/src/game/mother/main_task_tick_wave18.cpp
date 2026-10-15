#include "th10/platform/sound_fade_manager_wave18.hpp"
#pragma code_seg(".text$00b2_main")
__declspec(noinline) int __fastcall MainTaskTickWave18(MainTaskStateWave18* state) {
    if ((state->flags_3CC & 0x80) != 0 && state->state_63C == 0)
        data_00491fb8 = 3;
    g_sound_manager.TickFades();
    PollInputWave18(0);
    if (AnmPendingWave18(g_sprt_ctrl)) return 4;
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

// The mode update's private callees.
#include "../../../build_support/layout/ltcg/sound_fade_wave18_dependencies.cpp"
