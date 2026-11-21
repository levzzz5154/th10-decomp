#include "th10/platform/sound_fade_manager_wave18.hpp"

enum MainTaskTickFlags {
    APP_FLAG_CLOSING = 0x80,
    MAIN_MODE_QUIT_REQ = 3,
    MAIN_REQUEST_QUIT = 2,
    MAIN_TICK_CONTINUE = 1,
    MAIN_TICK_STOP = 4
};

#pragma code_seg(".text$00b2_main")
__declspec(noinline) int __fastcall MainTaskTickWave18(MainTaskStateWave18* state) {
    if ((state->flags_3CC & APP_FLAG_CLOSING) != 0 && state->state_63C == 0)
        g_main_state = MAIN_MODE_QUIT_REQ;
    g_sound_manager.TickFades();
    PollInputWave18(0);
    if (AnmPendingWave18(g_sprt_ctrl)) return MAIN_TICK_STOP;
    int request = state->request_648;
    if (request) {
        // MATCH: retail encodes the two statuses as a mask: request 2 returns 4,
        // while every other nonzero request returns 1.
        int other_request = request != MAIN_REQUEST_QUIT;
        return ((other_request - 1) & 3) + 1;
    }
    int result = state->UpdateMode();
    if (result == MAIN_TICK_CONTINUE) return MAIN_TICK_CONTINUE;
    return result;
}
#pragma code_seg()
