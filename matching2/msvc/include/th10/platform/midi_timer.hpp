#pragma once

// Slot zero is the timer event handler. The sequencer vtable at 0x0046F80C
// supplies the MIDI tick routine at 0x0043AF30.
struct MidiTimerTarget {
    virtual int OnTimer() = 0;
};

// WinMM's five-argument timer callback passes its user pointer third.
void __stdcall MidiTimer_Callback(unsigned int timer_id, unsigned int message,
                                 MidiTimerTarget* target,
                                 unsigned int parameter1,
                                 unsigned int parameter2);
