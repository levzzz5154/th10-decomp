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

struct MidiFileTrack {
    uint32_t active;
    uint32_t next_event_time;
    uint32_t data_size;
    uint32_t reserved_0c;
    uint8_t* data;
    uint32_t reserved_14[3];
};

struct MidiFileState {
    uint32_t format;
    uint32_t track_count;
    uint32_t division;
    MidiFileTrack* tracks;
    int source_slot;
    uint32_t tempo_microseconds;
};

struct MidiFileMemory {
    void* context;
    void* (*allocate)(void* context, uint32_t size);
    void (*release)(void* context, void* memory);
};

// 0x0043AAD0 - release the previous track table and parse one in-memory
// standard MIDI file into independently owned track buffers.
int MidiFile_Load(MidiFileState* state, const uint8_t* image,
                  uint32_t image_size, int source_slot,
                  const MidiFileMemory* memory);

struct MidiPlaybackTrack {
    uint32_t active;
    uint32_t next_event_time;
    uint32_t reserved[6];
};

struct MidiPlaybackState {
    uint32_t track_count;          // retail +0x118
    MidiPlaybackTrack* tracks;     // retail +0x138
    uint32_t time_numerator;       // retail +0x120
    uint32_t time_divisor;         // retail +0x124
    uint64_t tick;                 // retail +0x128/+0x12C
    uint64_t time_base;            // retail +0x130/+0x134
    float fade_volume;             // retail +0x2C8
    uint32_t fade_volume_step;     // retail +0x2CC
    uint32_t fade_active;          // retail +0x2E0
    uint32_t fade_duration;        // retail +0x2E4
    uint32_t fade_position;        // retail +0x2E8
};

struct MidiPlaybackHooks {
    void* context;
    void (*process_event)(void* context, MidiPlaybackState* state,
                          MidiPlaybackTrack* track);
    void (*apply_channel_volumes)(void* context, int delta);
    void (*rewind)(void* context, MidiPlaybackState* state);
};

// 0x0043AF30 - advance one MIDI sequencer tick. Returns nonzero when at
// least one track remains active; otherwise rewinds the sequencer and returns
// the rewind hook's result.
int MidiPlayback_Tick(MidiPlaybackState* state,
                      const MidiPlaybackHooks* hooks);
