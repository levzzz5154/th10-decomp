#ifndef TH10_PLATFORM_MIDI_SEQUENCER_HPP
#define TH10_PLATFORM_MIDI_SEQUENCER_HPP

#include <stddef.h>

struct midihdr_tag;

struct MidiTrack {
    int active;                         // +0x00
    int next_event_time;                // +0x04
    unsigned int byte_count;             // +0x08
    unsigned char running_status;       // +0x0C
    unsigned char unknown_0d[3];
    unsigned char* data;                // +0x10: owned track bytes
    const unsigned char* cursor;        // +0x14
    const unsigned char* loop_cursor;   // +0x18
    int saved_loop_time;                // +0x1C
};

// Partial sequencer layout. The timer base and unused fields remain opaque.
struct MidiSequencer {
    unsigned char timer_storage[0x10];
    int current_file_slot;              // +0x10: -1 when inactive
    midihdr_tag* midi_headers[32];       // +0x14
    int midi_header_index;              // +0x94
    unsigned char* file_buffers[32];     // +0x98
    int track_count;                    // +0x118
    int format;                         // +0x11C
    int ticks_per_quarter_note;          // +0x120
    int tempo_microseconds;             // +0x124
    unsigned __int64 elapsed_timer_ticks; // +0x128
    unsigned __int64 event_tick_base;    // +0x130
    MidiTrack* tracks;                   // +0x138
    unsigned char unknown_13c[0x18C];
    float fade_volume;                  // +0x2C8
    unsigned char unknown_2cc[0x10];
    unsigned int unknown_2dc;
    int fade_active;                    // +0x2E0

    __declspec(noinline) void ResetTracks();
    __declspec(noinline) void ReleaseTracks();
    __declspec(noinline) int ParseLoadedFile(int slot);
};

// Native LTCG selects ESI for &cursor and EDI for ResetTracks' this pointer.
__declspec(noinline) int __stdcall ReadMidiVariableLength(const unsigned char*& cursor);

typedef char MidiTrack_size[sizeof(MidiTrack) == 0x20 ? 1 : -1];
typedef char MidiTrack_data_offset[offsetof(MidiTrack, data) == 0x10 ? 1 : -1];
typedef char MidiTrack_cursor_offset[offsetof(MidiTrack, cursor) == 0x14 ? 1 : -1];
typedef char MidiTrack_loop_cursor_offset[offsetof(MidiTrack, loop_cursor) == 0x18 ? 1 : -1];
typedef char MidiSequencer_slot_offset[offsetof(MidiSequencer, current_file_slot) == 0x10 ? 1 : -1];
typedef char MidiSequencer_headers_offset[offsetof(MidiSequencer, midi_headers) == 0x14 ? 1 : -1];
typedef char MidiSequencer_header_index_offset[offsetof(MidiSequencer, midi_header_index) == 0x94 ? 1 : -1];
typedef char MidiSequencer_files_offset[offsetof(MidiSequencer, file_buffers) == 0x98 ? 1 : -1];
typedef char MidiSequencer_count_offset[offsetof(MidiSequencer, track_count) == 0x118 ? 1 : -1];
typedef char MidiSequencer_elapsed_offset[offsetof(MidiSequencer, elapsed_timer_ticks) == 0x128 ? 1 : -1];
typedef char MidiSequencer_tick_base_offset[offsetof(MidiSequencer, event_tick_base) == 0x130 ? 1 : -1];
typedef char MidiSequencer_tracks_offset[offsetof(MidiSequencer, tracks) == 0x138 ? 1 : -1];
typedef char MidiSequencer_volume_offset[offsetof(MidiSequencer, fade_volume) == 0x2C8 ? 1 : -1];
typedef char MidiSequencer_unknown_2dc_offset[offsetof(MidiSequencer, unknown_2dc) == 0x2DC ? 1 : -1];
typedef char MidiSequencer_fade_offset[offsetof(MidiSequencer, fade_active) == 0x2E0 ? 1 : -1];

#endif
