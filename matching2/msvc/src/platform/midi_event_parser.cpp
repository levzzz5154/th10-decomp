// 0x0043B110: the MIDI event parser. It reads one event from a track, updates
// the sequencer's channel state, forwards the message to the output device and
// schedules the track's next event.
#include "asm_symbols.hpp"
#include <string.h>
#include "th10/platform/midi_sequencer.hpp"

// The Win32 MIDIHDR used by midiOutPrepareHeader and midiOutLongMsg.
struct MidiEventHeader {
    unsigned char* data;
    unsigned int buffer_length;
    unsigned int bytes_recorded;
    unsigned int user;
    unsigned int flags;
    MidiEventHeader* next;
    unsigned int reserved;
    unsigned int offset;
    unsigned int reserved2[8];
};

typedef char MidiHeader_must_be_0x40_bytes[sizeof(MidiEventHeader) == 0x40 ? 1 : -1];
typedef char MidiHeader_flags_offset[offsetof(MidiEventHeader, flags) == 0x10 ? 1 : -1];

// Tempo and position, saved and restored as a unit by the loop controllers.
#pragma pack(push, 4)
struct MidiLoopClock {
    int tempo_microseconds;
    unsigned __int64 elapsed_timer_ticks;
    unsigned __int64 event_tick_base;
};
#pragma pack(pop)

// What the sequencer remembers about one of the sixteen channels.
struct MidiChannelState {
    unsigned char held_notes[16];   // one bit per key
    unsigned char program;
    unsigned char bank;
    unsigned char pan;
    unsigned char reverb;
    unsigned char chorus;
    unsigned char volume;
    unsigned char scaled_volume;    // volume after the fade level
};

// The part of the sequencer that the shared header leaves opaque.
struct MidiPlaybackState {
    unsigned char reserved_000[0x124];
    MidiLoopClock clock;
    MidiTrack* tracks;
    void* output;
    unsigned char reserved_140[0x14];
    MidiChannelState channels[16];
    signed char transpose;
    unsigned char reserved_2c5[3];
    float fade_volume;
    unsigned char reserved_2cc[0x20];
    MidiLoopClock loop_clock;
};

typedef char MidiLoopClock_size[sizeof(MidiLoopClock) == 20 ? 1 : -1];
typedef char MidiChannelState_size[sizeof(MidiChannelState) == 0x17 ? 1 : -1];
typedef char MidiPlaybackState_output[offsetof(MidiPlaybackState, output) == 0x13c ? 1 : -1];
typedef char MidiPlaybackState_channels[offsetof(MidiPlaybackState, channels) == 0x154 ? 1 : -1];
typedef char MidiPlaybackState_transpose[offsetof(MidiPlaybackState, transpose) == 0x2c4 ? 1 : -1];
typedef char MidiPlaybackState_loop_clock[offsetof(MidiPlaybackState, loop_clock) == 0x2ec ? 1 : -1];

typedef unsigned int (__stdcall *MidiOutPrepareHeaderCall)(void*, MidiEventHeader*, unsigned int);
typedef unsigned int (__stdcall *MidiOutLongMsgCall)(void*, MidiEventHeader*, unsigned int);
typedef unsigned int (__stdcall *MidiOutShortMsgCall)(void*, unsigned int);

static __forceinline MidiOutPrepareHeaderCall MidiOutPrepareHeaderImport() {
    return *reinterpret_cast<MidiOutPrepareHeaderCall*>(&data_004662a0);
}

static __forceinline MidiOutLongMsgCall MidiOutLongMsgImport() {
    return *reinterpret_cast<MidiOutLongMsgCall*>(&data_0046629c);
}

static __forceinline MidiOutShortMsgCall MidiOutShortMsgImport() {
    return *reinterpret_cast<MidiOutShortMsgCall*>(&data_00466298);
}

static __forceinline unsigned int ReadMidiEventValue(const unsigned char*& cursor) {
    unsigned int value = 0;
    unsigned char byte;
    do {
        byte = *cursor++;
        value = value * 0x80 + (byte & 0x7f);
    } while ((byte & 0x80) != 0);
    return value;
}

// Prepare and queue a system-exclusive buffer; nonzero when it was refused.
static __forceinline int SendMidiLongMessage(MidiPlaybackState* state, MidiEventHeader* header) {
    if (state->output == 0)
        return 0;
    if (MidiOutPrepareHeaderImport()(state->output, header, 0x40) != 0)
        return 1;
    return MidiOutLongMsgImport()(state->output, header, 0x40) != 0;
}

extern "C" __declspec(noinline) int CompleteMidiHeader_0043aeb0(
    MidiSequencer*, midihdr_tag*);

// Timer ticks since the last tempo change, in MIDI ticks.
static __forceinline unsigned __int64 MidiEventElapsedTicks(MidiSequencer* sequencer) {
    return (static_cast<unsigned __int64>(static_cast<__int64>(
                sequencer->ticks_per_quarter_note)) *
            sequencer->elapsed_timer_ticks * 1000) /
        static_cast<unsigned __int64>(static_cast<__int64>(
            sequencer->tempo_microseconds));
}

#pragma code_seg(".text$60parser")
extern "C" __declspec(noinline) void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer,
    MidiTrack* track) {
    unsigned char data1 = 0;
    unsigned char data2 = 0;
    unsigned char status = *track->cursor;
    if (status < 0x80) {
        // A data byte: the previous status byte still applies.
        status = track->running_status;
    } else {
        ++track->cursor;
    }

    const unsigned char channel = status & 0x0f;
    const unsigned char message_type = status & 0xf0;
    switch (message_type) {
    case 0xf0:
        if (status == 0xf0) {
            // System exclusive: hand the payload to the device in its own
            // buffer, kept in a ring of 32 until the device returns it.
            if (sequencer->midi_headers[sequencer->midi_header_index] != 0)
                CompleteMidiHeader_0043aeb0(sequencer,
                    sequencer->midi_headers[sequencer->midi_header_index]);

            sequencer->midi_headers[sequencer->midi_header_index] =
                static_cast<midihdr_tag*>(asm_malloc_00452706(0x40));
            MidiEventHeader* header = reinterpret_cast<MidiEventHeader*>(
                sequencer->midi_headers[sequencer->midi_header_index]);
            const int length = ReadMidiVariableLength(track->cursor);

            memset(header, 0, sizeof(*header));

            header->data = static_cast<unsigned char*>(asm_malloc_00452706(length + 1));
            header->data[0] = 0xf0;
            header->flags = 0;
            header->buffer_length = length + 1;
            int index;
            for (index = 0; index < length; ++index)
                header->data[index + 1] = *track->cursor++;

            if (SendMidiLongMessage(reinterpret_cast<MidiPlaybackState*>(sequencer), header)) {
                if (header->data != 0) {
                    asm_free_00452422(header->data);
                    header->data = 0;
                }
                asm_free_00452422(header);
                sequencer->midi_headers[sequencer->midi_header_index] = 0;
            }

            sequencer->midi_header_index = (sequencer->midi_header_index + 1) % 32;
        } else if (status == 0xff) {
            // Meta event.
            const unsigned char meta_type = *track->cursor++;
            const int length = ReadMidiVariableLength(track->cursor);
            if (meta_type == 0x2f) {
                // End of track.
                track->active = 0;
                return;
            }

            if (meta_type == 0x51) {
                // Tempo change: bank the time played at the old tempo first.
                sequencer->event_tick_base += MidiEventElapsedTicks(sequencer);
                sequencer->elapsed_timer_ticks = 0;
                sequencer->tempo_microseconds = 0;
                int index;
                for (index = 0; index < length; ++index) {
                    sequencer->tempo_microseconds =
                        sequencer->tempo_microseconds * 0x101 + *track->cursor++;
                }
            } else {
                track->cursor += length;
            }
        }
        break;
    case 0x80:
    case 0x90:
    case 0xa0:
    case 0xb0:
    case 0xe0:
        data1 = *track->cursor++;
        data2 = *track->cursor++;
        break;
    case 0xc0:
    case 0xd0:
        data1 = *track->cursor++;
        data2 = 0;
        break;
    }

    MidiPlaybackState* state = reinterpret_cast<MidiPlaybackState*>(sequencer);
    switch (message_type) {
    case 0x90:
        if (data2 != 0) {
            data1 += state->transpose;
            state->channels[channel].held_notes[data1 >> 3] |= 1 << (data1 & 7);
            break;
        }
        // A note-on with zero velocity releases the key.
    case 0x80:
        data1 += state->transpose;
        state->channels[channel].held_notes[data1 >> 3] &= ~(1 << (data1 & 7));
        break;
    case 0xc0:
        state->channels[channel].program = data1;
        break;
    case 0xb0:
        switch (data1) {
        case 0:
            state->channels[channel].bank = data2;
            break;
        case 7: {
            state->channels[channel].volume = data2;
            int volume = static_cast<int>(static_cast<float>(data2) * state->fade_volume);
            if (volume < 0)
                volume = 0;
            else if (volume > 0x7f)
                volume = 0x7f;
            state->channels[channel].scaled_volume = static_cast<unsigned char>(volume);
            data2 = static_cast<unsigned char>(volume);
            break;
        }
        case 0x5b:
            state->channels[channel].reverb = data2;
            break;
        case 0x5d:
            state->channels[channel].chorus = data2;
            break;
        case 10:
            state->channels[channel].pan = data2;
            break;
        case 2: {
            // Loop start: remember every track's position and the clock.
            MidiTrack* saved_track = state->tracks;
            int index;
            for (index = 0; index < sequencer->track_count; ++index, ++saved_track) {
                saved_track->loop_cursor = saved_track->cursor;
                saved_track->saved_loop_time = saved_track->next_event_time;
            }
            state->loop_clock.tempo_microseconds = state->clock.tempo_microseconds;
            state->loop_clock.elapsed_timer_ticks = state->clock.elapsed_timer_ticks;
            state->loop_clock.event_tick_base = state->clock.event_tick_base;
            break;
        }
        case 4: {
            // Loop end: jump back to the remembered position.
            MidiTrack* saved_track = state->tracks;
            int index;
            for (index = 0; index < sequencer->track_count; ++index, ++saved_track) {
                saved_track->cursor = saved_track->loop_cursor;
                saved_track->next_event_time = saved_track->saved_loop_time;
            }
            state->clock.tempo_microseconds = state->loop_clock.tempo_microseconds;
            state->clock.elapsed_timer_ticks = state->loop_clock.elapsed_timer_ticks;
            state->clock.event_tick_base = state->loop_clock.event_tick_base;
            break;
        }
        }
        break;
    }

    if (status < 0xf0 && state->output != 0) {
        union { unsigned int word; unsigned char bytes[4]; } message;
        message.bytes[1] = data1;
        message.bytes[0] = status;
        message.bytes[2] = data2;
        MidiOutShortMsgImport()(state->output, message.word);
    }

    track->running_status = status;
    track->next_event_time += ReadMidiEventValue(track->cursor);
}
#pragma code_seg()
