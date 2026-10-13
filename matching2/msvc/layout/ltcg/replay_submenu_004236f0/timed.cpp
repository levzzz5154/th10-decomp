#include "th10/game/replay_submenu_004236f0/state.hpp"
// 0x00423510: reset a timed game-state record, point its curve timer at the
// shared speed value and stop both of the animation handles it carries.
// Retail enters this member with the record in ESI.
extern "C" float data_00476f78;
#pragma code_seg(".text$02f")
void SubTimedState_004236f0::InitializeTimedState() {
    int* record = &state;
    record[0] = 13;
    if ((timer_flags & 1) == 0) {
        timer_current = 0;
        timer_previous = 0xFFF0BDC1;
        timer_elapsed = 0;
        timer_speed = &data_00476f78;
        timer_flags |= 1;
    }
    timer_current = 0;
    timer_elapsed = 0;
    timer_previous = -1;
    handle_1d8.StopAtFrame1();
    handle_1d4.StopAtFrame1();
    data_00476f78 = speed;
}
#pragma code_seg()
