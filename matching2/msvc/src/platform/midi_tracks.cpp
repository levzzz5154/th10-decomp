#include "th10/platform/midi_sequencer.hpp"

#pragma code_seg(".text$10read")
static inline unsigned int ReadVariableLength(const unsigned char*& cursor) {
    unsigned int value = 0;
    unsigned char byte;
    do {
        byte = *cursor++;
        value = (value << 7) + (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}

// 0x0043A730: advance the cursor through one MIDI variable-length quantity.
int __stdcall ReadMidiVariableLength(const unsigned char*& cursor) {
    return static_cast<int>(ReadVariableLength(cursor));
}

// 0x0043ACE0: rewind the tracks and read their initial event delays.
#pragma code_seg(".text$30reset")
void MidiSequencer::ResetTracks() {
    MidiTrack* track = tracks;
    fade_volume = 1.0f;
    unknown_2dc = 0;
    fade_active = 0;
    elapsed_timer_ticks = 0;
    event_tick_base = 0;
    for (int index = 0; index < track_count; ++index, ++track) {
        track->cursor = track->data;
        track->loop_cursor = track->data;
        track->active = 1;
        track->next_event_time = static_cast<int>(ReadVariableLength(track->cursor));
    }
}
#pragma code_seg()
