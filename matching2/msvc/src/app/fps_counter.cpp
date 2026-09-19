// 0x004134B0..0x004135C8 (280 bytes): FrameRateCounter::Update.
//
// The counter's per-frame update: clamp the timer delta that
// 0x00439540 `FrameTimer_GetDelta` reports, refuse the frame when less than half
// a second of it elapsed, turn the frame interval into a frame rate, and adjust
// the frame-skip bookkeeping when the rate leaves the 57/65 Hz band.
//
// The counter object arrives in ESI - the dispatcher 0x004135D0 marshals it with
// `mov esi,edi` before the call and overwrites ESI immediately after - which only
// the whole-program pass of a native /LTCG link can select, so this body is a
// single-function cluster (layout/ltcg/fps_counter_004134b0.json).
//
// Three measured shape levers, not recovered style:
//
//   * `__declspec(align(8)) float rate` is the construct that makes MSVC frame
//     this function with `and esp,-8` and a 4-byte 8-aligned local (`push ecx`).
//     The value still lives in an x87 register - the frame slot is never read -
//     so the lever costs no instruction.
//   * the stall guard is spelled `if (delta >= 0.5) { ... return 1; }` with the
//     shared `return 1;` after it. That is the only spelling of the guard that
//     puts its exit block out of line at the end of the function, where retail
//     jumps to it with `test ah,1; jne 0x4135BC` (the natural `if (delta < 0.5)
//     return 1;` inlines the exit and emits the inverted `test ah,5; jp`, four
//     bytes short).
//   * the frame-event counter is cleared inside the `== 4` arm as well as in the
//     `else` arm, so the two arms keep their own timer snapshot. Written with a
//     single `else` the compiler merges the two identical snapshot tails into
//     one and the body shrinks by 15 bytes.

extern "C" double __cdecl FrameTimer_GetDelta(void);   // 0x00439540

// Frame timer state the counter resets (see src/app/frame_clock.cpp for the
// routines that own it).
extern "C" long long data_00492508;   // 0x00492508  QPC ticks per second
extern "C" double data_00492528;      // 0x00492528
extern "C" double data_00492530;      // 0x00492530
extern "C" double data_00492538;      // 0x00492538
extern "C" double data_00492540;      // 0x00492540

// The slot owner whose flags gate the accounting below; the same object
// src/game/fun_004065c0_004065c0.cpp names RecoverySlotOwner_004065c0.
struct RecoverySlotOwner_004134b0 {
    unsigned char pad_00[0x58];
    unsigned int field_58;  // +0x58
};
extern "C" RecoverySlotOwner_004134b0* data_00477810;  // 0x00477810

// 4-byte packing is what puts the two doubles at +0x24/+0x2C: their retail
// offsets are 4 mod 8.
#pragma pack(push, 4)
struct FrameRateCounter_004134b0 {
    unsigned char pad_0000[0x14];
    double time_last;          // +0x14  clamped timer sample
    int frame_events;          // +0x1C  consecutive high-rate frames
    unsigned int frame_count;  // +0x20  game frames inside the interval
    double measured;           // +0x24
    double budget;             // +0x2C
    float fps;                 // +0x34
    __declspec(noinline) int Update();
};
#pragma pack(pop)

#pragma code_seg(".text$01update")
int FrameRateCounter_004134b0::Update() {
    double now = FrameTimer_GetDelta();
    if (now < time_last)
        time_last = now;                 // the clock went backwards: resync
    double delta = now - time_last;
    if (delta >= 0.5) {
        time_last = delta + time_last;
        __declspec(align(8)) float rate = (float)((double)frame_count / delta);
        fps = rate;
        if (rate > 65.0f) {
            if (++frame_events == 2) {
                data_00492530 = data_00492528 = data_00492538 = data_00492540 =
                    FrameTimer_GetDelta();
            } else if (frame_events == 4) {
                data_00492508 = 0;       // give up on the performance counter
                data_00492530 = data_00492528 = data_00492538 = data_00492540 =
                    FrameTimer_GetDelta();
                frame_events = 0;
            }
        } else {
            frame_events = 0;
        }
        if (data_00477810 != 0) {
            if ((data_00477810->field_58 & 0x14) == 0) {
                budget = budget + 60.0;
                if (fps > 57.0f)
                    measured = measured + 60.0;
                else
                    measured = fps + measured;
            }
            data_00477810->field_58 &= ~0x80u;
        }
        frame_count = 0;
        return 1;
    }
    return 1;
}
#pragma code_seg()
