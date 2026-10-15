#include "th10/platform/midi_timer.hpp"

// 0x0043A6E0: deliver a multimedia timer notification to its target.
void __stdcall MidiTimer_Callback(unsigned int, unsigned int,
                                 MidiTimerTarget* target,
                                 unsigned int, unsigned int) {
    target->OnTimer();
}
