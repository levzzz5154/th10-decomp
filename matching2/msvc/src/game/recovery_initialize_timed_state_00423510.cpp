// 0x00423510..0x00423568: reset a timed game-state record, point its curve
// timer at the shared speed value and stop both of the animation handles it
// carries.
//
// Retail enters this member with the record in ESI, a receiver no C++
// declaration names, so the body is compiled in the native-LTCG cluster
// layout/ltcg/stop_at_frame_pair_0040c480.json whose synthetic caller
// establishes that register.  The two handles at +0x1D4/+0x1D8 are
// AnimationHandles, so the calls reach the StopAtFrame1 body that same cluster
// already carries with its address in EAX.
//
// The record repeats the score-timer shape (previous/current/elapsed/speed/
// flags, see src/game/score_timer_leaves.cpp) at +0x10 instead of +0x2B0, and
// copies its own speed field out to the shared float the timer reads.
//
// The state store reaches the record through a pointer to that field rather
// than through the member: as ``int* base = &record->state`` the store keeps its
// place in front of the flag load, while the direct member store sinks into the
// compare slot (12 bytes away from the retail schedule).

#include "th10/render/animation_handle.hpp"

extern "C" float data_00476f78;

struct RecoveryTimedState_00423510 {
    unsigned char unknown_00[0x04];
    int state;                                 // +0x04
    unsigned char unknown_08[0x08];
    int timer_previous;                        // +0x10
    int timer_current;                         // +0x14
    int timer_elapsed;                         // +0x18
    float* timer_speed;                        // +0x1C
    unsigned int timer_flags;                  // +0x20
    unsigned char unknown_24[0x1B0];
    AnimationHandle handle_1d4;                // +0x1D4
    AnimationHandle handle_1d8;                // +0x1D8
    unsigned char unknown_1dc[0xE4];
    float speed;                               // +0x2C0

    __declspec(noinline) void InitializeTimedState();
};

typedef char RecoveryTimedState_00423510_size_must_fit[
    sizeof(RecoveryTimedState_00423510) == 0x2C4 ? 1 : -1];

#pragma code_seg(".text$45timed")
void RecoveryTimedState_00423510::InitializeTimedState() {
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
