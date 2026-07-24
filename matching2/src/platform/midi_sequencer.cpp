#include "th10/platform/midi_sequencer.hpp"

// 0x0043A730 - Read one standard MIDI variable-length quantity:
// accumulate seven payload bits per byte while the continuation bit
// (0x80) is set, advancing the cursor past every byte read.
int32_t Midi_ReadVariableLength(const uint8_t** cursor) {
    int32_t value = 0;
    uint8_t byte;
    do {
        byte = **cursor;
        *cursor += 1;
        value = value * 0x80 + (byte & 0x7F);
    } while ((byte & 0x80) != 0);
    return value;
}

// 0x0043ACE0 - Rewind the sequencer. Retail clears the elapsed pair at
// +0x2DC/+0x2E0 and the four position words at +0x128..+0x134, resets
// the tempo scale at +0x2C8 to 1.0, and walks the track table at +0x138
// (count at +0x118): each track's cursor and loop pointer rewind to the
// chunk start, the active word becomes 1, and the first event delta is
// primed with the inlined variable-length read (the same loop as
// 0x0043A730).
void MidiSequencer_ResetTracks(MidiSequencer* sequencer) {
    sequencer->tempo_scale = 1.0f;
    sequencer->elapsed_low = 0;
    sequencer->elapsed_high = 0;
    sequencer->position = 0;
    sequencer->position_2 = 0;
    sequencer->position_3 = 0;
    sequencer->position_4 = 0;
    for (int32_t index = 0; index < sequencer->track_count; ++index) {
        MidiTrack* track = &sequencer->tracks[index];
        track->cursor = track->data;
        track->loop_start = track->data;
        track->active = 1;
        track->next_event_delta = Midi_ReadVariableLength(&track->cursor);
    }
}
