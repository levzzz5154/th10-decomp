// 0x0042C5C0..0x0042C612 (83 bytes): point the score timer at a new owner and
// reset its countdown.
//
// Retail enters this member with the timer state in EAX and the owner in ECX, a
// convention no C++ declaration can name, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/timer_owner_0042c5c0.json, whose synthetic
// caller establishes that pair.  The body itself is ordinary readable C++.
//
// The record is the same 0x2C4-byte score timer the title-options setter
// (0x0042C620, src/game/title/title_set_timer_target.cpp) drives: the countdown lives at +0x2B0
// (previous), +0x2B4 (current), +0x2B8 (elapsed), +0x2BC (speed) and +0x2C0
// (flags; bit 0 is "running").  This entry additionally records the owner at
// +0x1C and clears the pending target at +0x20 before the reset.
//
// The owner slot and the pending target are written as one pair through a base
// pointer.  Without the shared base the backend sinks the second store into the
// compare slot of the flag test (`test cl,1` / store / `jne`), which is two
// bytes and three instructions away from retail's schedule; with it the two
// stores stay adjacent before the flag load, exactly as retail emits them.
extern "C" float data_00476f78;

struct Title {
    unsigned char unknown_00[0x1C];
    int timer_owner;                 // +0x1C
    int timer_target;                // +0x20
    unsigned char unknown_24[0x28C];
    int timer_previous;              // +0x2B0
    int timer_current;               // +0x2B4
    int timer_elapsed;               // +0x2B8
    float* timer_speed;              // +0x2BC
    unsigned int timer_flags;        // +0x2C0

    __declspec(noinline) void DisableTimerWithOwner(int owner);
};

typedef char Title_size_must_fit[
    sizeof(Title) == 0x2C4 ? 1 : -1];

#pragma code_seg(".text$01accessor")
void Title::DisableTimerWithOwner(int owner) {
    int* request = &timer_owner;
    request[0] = owner;
    request[1] = 0;
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
}
#pragma code_seg()
