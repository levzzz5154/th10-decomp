#pragma once

#include <cstdint>

// One sequencer track record (retail 0x20 bytes; word offsets in
// comments -- the data pointers are 32-bit slots in retail).
struct MidiTrack {
    uint32_t active;            // word 0, set to 1 on reset
    int32_t next_event_delta;   // word 1, first varint of the track
    uint32_t reserved_08;       // word 2
    uint32_t reserved_0c;       // word 3
    const uint8_t* data;        // word 4, start of the track chunk
    const uint8_t* cursor;      // word 5, read position
    const uint8_t* loop_start;  // word 6, rewound with the cursor
    uint32_t reserved_1c;       // word 7
};

// Sequencer fragment (retail offsets in comments).
struct MidiSequencer {
    int32_t track_count;    // +0x118
    MidiTrack* tracks;      // +0x138
    float tempo_scale;      // +0x2C8, reset to 1.0f
    uint32_t elapsed_low;   // +0x2DC
    uint32_t elapsed_high;  // +0x2E0
    uint32_t position;      // +0x128
    uint32_t position_2;    // +0x12C
    uint32_t position_3;    // +0x130
    uint32_t position_4;    // +0x134
};

// 0x0043A730 - Read one standard MIDI variable-length quantity at the
// cursor, advancing it. Retail keeps the cursor pointer in ESI.
int32_t Midi_ReadVariableLength(const uint8_t** cursor);

// 0x0043ACE0 - Rewind the sequencer: reset the tempo scale and the
// elapsed/position accumulators, then rewind every track's cursor and
// loop pointer to the track data start, mark it active, and prime its
// first event delta by reading the leading variable-length quantity.
void MidiSequencer_ResetTracks(MidiSequencer* sequencer);
