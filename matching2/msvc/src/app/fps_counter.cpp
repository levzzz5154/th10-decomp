// Complete frame-rate update0x004134B0, with its real FPS draw and scheduler callback.
// Native LTCG preserves the original ESI receiver in Update, EDI receiver in Draw,
// and ECX scheduler boundary. The original variadic formatter and queue writer
// are part of this same genuine caller/callee closure.

extern "C" double __cdecl FrameTimer_GetDelta(void);   // 0x00439540

// Frame timer state the counter resets (see src/core/main/frame_clock.cpp for the
// routines that own it).
extern "C" long long data_00492508;   // 0x00492508  QPC ticks per second
extern "C" double data_00492528;      // 0x00492528
extern "C" double data_00492530;      // 0x00492530
extern "C" double data_00492538;      // 0x00492538
extern "C" double data_00492540;      // 0x00492540

// The slot owner whose flags gate the accounting below; the same object
// src/game/bullet/fun_004065c0_004065c0.cpp names RecoverySlotOwner_004065c0.
struct RecoverySlotOwner_004134b0 {
    unsigned char pad_00[0x58];
    unsigned int field_58;  // +0x58
};
extern "C" RecoverySlotOwner_004134b0* data_00477810;  // 0x00477810

// 4-byte packing is what puts the two doubles at +0x24/+0x2C: their retail
// offsets are 4 mod 8.
#include "th10/app/frame_rate_counter_native.hpp"

#pragma code_seg(".text$05update")
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


#include "../game/ascii/add_formatted_marked.cpp"
#include "fun_004135d0_004135d0.cpp"
#include "fps_counter_on_draw.cpp"

#include "../game/ascii/add_formatted.cpp"
#include "../game/replay_manager_draw.cpp"
