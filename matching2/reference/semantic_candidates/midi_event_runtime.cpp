// Superseded: the parser is recovered in msvc/src/platform/midi_event_parser.cpp.
// This earlier candidate is kept only because the dated notes refer to it.
#include "asm_symbols.hpp"
#include <string.h>
#include "th10/platform/midi_sequencer.hpp"

// This is the Win32 layout used by midiOutPrepareHeader and midiOutLongMsg.
// MidiSequencer's public header deliberately leaves the header array opaque.
struct MidiEventHeader {
    char* lpData;
    unsigned int dwBufferLength;
    unsigned int dwBytesRecorded;
    unsigned int dwUser;
    unsigned int dwFlags;
    MidiEventHeader* lpNext;
    unsigned int dwReserved;
    unsigned int dwOffset;
    unsigned int dwReserved2[8];
};

typedef char MidiHeader_must_be_0x40_bytes[sizeof(MidiEventHeader) == 0x40 ? 1 : -1];
typedef char MidiHeader_flags_offset[offsetof(MidiEventHeader, dwFlags) == 0x10 ? 1 : -1];

// The loop clock at +0x2ec is only DWORD aligned in the retail object.
#pragma pack(push, 4)
struct MidiLoopClock {
    int tempo_microseconds;
    unsigned __int64 elapsed_timer_ticks;
    unsigned __int64 event_tick_base;
};
#pragma pack(pop)
typedef char MidiLoopClock_size[sizeof(MidiLoopClock) == 20 ? 1 : -1];
typedef char MidiLoopClock_elapsed_offset[offsetof(MidiLoopClock, elapsed_timer_ticks) == 4 ? 1 : -1];
typedef char MidiLoopClock_base_offset[offsetof(MidiLoopClock, event_tick_base) == 12 ? 1 : -1];

typedef unsigned int (__stdcall *MidiOutPrepareHeaderCall)(void*, MidiEventHeader*, unsigned int);
typedef unsigned int (__stdcall *MidiOutLongMsgCall)(void*, MidiEventHeader*, unsigned int);
typedef unsigned int (__stdcall *MidiOutShortMsgCall)(void*, unsigned int);

static __forceinline MidiOutPrepareHeaderCall MidiOutPrepareHeaderAtRetail() {
    return *reinterpret_cast<MidiOutPrepareHeaderCall*>(&data_004662a0);
}

static __forceinline MidiOutLongMsgCall MidiOutLongMsgAtRetail() {
    return *reinterpret_cast<MidiOutLongMsgCall*>(&data_0046629c);
}

static __forceinline MidiOutShortMsgCall MidiOutShortMsgAtRetail() {
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

// Co-compile the maintained helper bodies to derive their private register
// ABIs. An ordinary external declaration alone cannot prove those boundaries.
extern "C" __declspec(noinline) int CompleteMidiHeader_0043aeb0(
    MidiSequencer*, midihdr_tag*);

static __forceinline unsigned __int64 MidiEventElapsedTicks(MidiSequencer* sequencer) {
    // Retail CDQ sign-extends both 32-bit inputs; its division is unsigned.
    // Native operators let MSVC emit the original runtime-helper calls.
    return (static_cast<unsigned __int64>(static_cast<__int64>(
                sequencer->ticks_per_quarter_note)) *
            sequencer->elapsed_timer_ticks * 1000) /
        static_cast<unsigned __int64>(static_cast<__int64>(
            sequencer->tempo_microseconds));
}

// 0x0043B110 parses and applies one MIDI event from a track.  The live caller
// pushes (track, sequencer), and the retail function returns with ret 8, so
// the native boundary is a two-argument stdcall routine.
extern "C" __declspec(noinline) void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer,
    MidiTrack* track) {
    unsigned char status = *track->cursor;
    unsigned char data1 = 0;
    unsigned char data2 = 0;
    // Retail packs the output into the incoming track-pointer stack slot.
    // Controller 7 overwrites that slot with its zero-extended input first.
    unsigned int message_storage = reinterpret_cast<unsigned int>(track);
    if (status < 0x80) {
        status = track->running_status;
    } else {
        ++track->cursor;
    }

    const unsigned char channel = status & 0x0f;
    const unsigned char messageType = status & 0xf0;
    switch (messageType) {
    case 0x80:
    case 0x90:
    case 0xa0:
    case 0xb0:
    case 0xe0: {
        data1 = *track->cursor++;
        data2 = *track->cursor++;
        break;
    }
    case 0xc0:
    case 0xd0: {
        data1 = *track->cursor++;
        break;
    }
    case 0xf0: {
        if (status == 0xf0) {
            if (sequencer->midi_headers[sequencer->midi_header_index] != 0)
                CompleteMidiHeader_0043aeb0(sequencer,
                    sequencer->midi_headers[sequencer->midi_header_index]);

            sequencer->midi_headers[sequencer->midi_header_index] =
                static_cast<midihdr_tag*>(asm_malloc_00452706(0x40));
            MidiEventHeader* header = reinterpret_cast<MidiEventHeader*>(
                sequencer->midi_headers[sequencer->midi_header_index]);
            const int sysexLength = ReadMidiVariableLength(track->cursor);

            memset(header, 0, sizeof(*header));

            header->lpData = static_cast<char*>(asm_malloc_00452706(
                static_cast<unsigned int>(sysexLength) + 1));
            header->lpData[0] = static_cast<char>(0xf0);
            header->dwFlags = 0;
            header->dwBufferLength = static_cast<unsigned int>(sysexLength) + 1;
            int byteIndex;
            for (byteIndex = 0; byteIndex < sysexLength; ++byteIndex)
                header->lpData[byteIndex + 1] = static_cast<char>(*track->cursor++);

            void*& output = *reinterpret_cast<void**>(
                reinterpret_cast<unsigned char*>(sequencer) + 0x13c);
            if (output != 0 &&
                (MidiOutPrepareHeaderAtRetail()(output, header, 0x40) != 0 ||
                 MidiOutLongMsgAtRetail()(output, header, 0x40) != 0)) {
                if (header->lpData != 0) {
                    asm_free_00452422(header->lpData);
                    header->lpData = 0;
                }
                asm_free_00452422(header);
                sequencer->midi_headers[sequencer->midi_header_index] = 0;
            }

            // Retail uses signed remainder, including its negative-index path.
            sequencer->midi_header_index = static_cast<int>(
                static_cast<unsigned int>(sequencer->midi_header_index) + 1) % 32;
        } else if (status == 0xff) {
            const unsigned char metaType = *track->cursor++;
            const int metaLength = ReadMidiVariableLength(track->cursor);
            if (metaType == '/') {
                track->active = 0;
                return;
            }

            if (metaType == 'Q') {
                sequencer->event_tick_base += MidiEventElapsedTicks(sequencer);
                sequencer->elapsed_timer_ticks = 0;
                sequencer->tempo_microseconds = 0;
                int byteIndex;
                for (byteIndex = 0; byteIndex < metaLength; ++byteIndex) {
                    sequencer->tempo_microseconds =
                        static_cast<int>(static_cast<unsigned int>(
                            sequencer->tempo_microseconds) * 0x101u + *track->cursor++);
                }
            } else {
                track->cursor += metaLength;
            }
        }
    }

    }

    unsigned char* state = reinterpret_cast<unsigned char*>(sequencer);
    switch (messageType) {
    case 0x90:
    if (data2 != 0) {
        const signed char transpose = *reinterpret_cast<signed char*>(state + 0x2c4);
        data1 = static_cast<unsigned char>(data1 + transpose);
        const unsigned char note = data1;
        unsigned char* noteBits = (state + 0x154 + channel * 0x17) + (note >> 3);
        *noteBits |= static_cast<unsigned char>(1u << (note & 7));
        break;
    }
    case 0x80: {
        const signed char transpose = *reinterpret_cast<signed char*>(state + 0x2c4);
        data1 = static_cast<unsigned char>(data1 + transpose);
        const unsigned char note = data1;
        unsigned char* noteBits = (state + 0x154 + channel * 0x17) + (note >> 3);
        *noteBits &= static_cast<unsigned char>(~(1u << (note & 7)));
        break;
    }
    case 0xb0: {
        switch (data1) {
        case 0:
            (state + 0x154 + channel * 0x17)[0x11] = data2;
            break;
        case 2: {
            MidiTrack* saved_track = sequencer->tracks;
            int index;
            for (index = 0; index < sequencer->track_count; ++index, ++saved_track) {
                saved_track->loop_cursor = saved_track->cursor;
                saved_track->saved_loop_time = saved_track->next_event_time;
            }
            MidiLoopClock& savedClock = *reinterpret_cast<MidiLoopClock*>(state + 0x2ec);
            savedClock.tempo_microseconds = sequencer->tempo_microseconds;
            savedClock.elapsed_timer_ticks = sequencer->elapsed_timer_ticks;
            savedClock.event_tick_base = sequencer->event_tick_base;
            break;
        }
        case 4: {
            MidiTrack* saved_track = sequencer->tracks;
            int index;
            for (index = 0; index < sequencer->track_count; ++index, ++saved_track) {
                saved_track->cursor = saved_track->loop_cursor;
                saved_track->next_event_time = saved_track->saved_loop_time;
            }
            const MidiLoopClock& savedClock = *reinterpret_cast<const MidiLoopClock*>(state + 0x2ec);
            sequencer->tempo_microseconds = savedClock.tempo_microseconds;
            sequencer->elapsed_timer_ticks = savedClock.elapsed_timer_ticks;
            sequencer->event_tick_base = savedClock.event_tick_base;
            break;
        }
        case 7: {
            (state + 0x154 + channel * 0x17)[0x15] = data2;
            message_storage = data2;
            int volume = static_cast<int>(static_cast<__int64>(
                static_cast<float>(data2) * sequencer->fade_volume));
            if (volume < 0) {
                (state + 0x154 + channel * 0x17)[0x16] = 0;
                data2 = 0;
            } else {
                if (volume > 0x7f)
                    volume = 0x7f;
                (state + 0x154 + channel * 0x17)[0x16] = static_cast<unsigned char>(volume);
                data2 = static_cast<unsigned char>(volume);
            }
            break;
        }
        case 10:
            (state + 0x154 + channel * 0x17)[0x12] = data2;
            break;
        case 0x5b:
            (state + 0x154 + channel * 0x17)[0x13] = data2;
            break;
        case 0x5d:
            (state + 0x154 + channel * 0x17)[0x14] = data2;
            break;
        }
        break;
    }
    case 0xc0: {
        (state + 0x154 + channel * 0x17)[0x10] = data1;
    }

    }

    void* output = *reinterpret_cast<void**>(state + 0x13c);
    if (status < 0xf0 && output != 0) {
        unsigned char* message_bytes = reinterpret_cast<unsigned char*>(&message_storage);
        message_bytes[1] = data1;
        message_bytes[0] = status;
        message_bytes[2] = data2;
        MidiOutShortMsgAtRetail()(output, message_storage);
    }

    track->running_status = status;
    const unsigned int delta = ReadMidiEventValue(track->cursor);
    track->next_event_time = static_cast<int>(
        static_cast<unsigned int>(track->next_event_time) + delta);
}
