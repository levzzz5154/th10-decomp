#include "asm_symbols.hpp"
#include "th10/platform/midi_sequencer.hpp"

// This is the Win32 layout used by midiOutPrepareHeader and midiOutLongMsg.
// MidiSequencer's public header deliberately leaves the header array opaque.
struct midihdr_tag {
    char* lpData;
    unsigned int dwBufferLength;
    unsigned int dwBytesRecorded;
    unsigned int dwUser;
    unsigned int dwFlags;
    midihdr_tag* lpNext;
    unsigned int dwReserved;
    unsigned int dwOffset;
    unsigned int dwReserved2[8];
};

typedef char MidiHeader_must_be_0x40_bytes[sizeof(midihdr_tag) == 0x40 ? 1 : -1];

typedef unsigned int (__stdcall *MidiOutPrepareHeaderCall)(void*, midihdr_tag*, unsigned int);
typedef unsigned int (__stdcall *MidiOutLongMsgCall)(void*, midihdr_tag*, unsigned int);
typedef unsigned int (__stdcall *MidiOutUnprepareHeaderCall)(void*, midihdr_tag*, unsigned int);
typedef unsigned int (__stdcall *MidiOutShortMsgCall)(void*, unsigned int);

static __forceinline MidiOutPrepareHeaderCall MidiOutPrepareHeaderAtRetail() {
    return *reinterpret_cast<volatile MidiOutPrepareHeaderCall*>(&data_004662a0);
}

static __forceinline MidiOutLongMsgCall MidiOutLongMsgAtRetail() {
    return *reinterpret_cast<volatile MidiOutLongMsgCall*>(&data_0046629c);
}

static __forceinline MidiOutUnprepareHeaderCall MidiOutUnprepareHeaderAtRetail() {
    return *reinterpret_cast<volatile MidiOutUnprepareHeaderCall*>(&data_00466284);
}

static __forceinline MidiOutShortMsgCall MidiOutShortMsgAtRetail() {
    return *reinterpret_cast<volatile MidiOutShortMsgCall*>(&data_00466298);
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

static __forceinline void ReleaseQueuedMidiHeader(
    MidiSequencer* sequencer,
    midihdr_tag* header) {
    int index;
    for (index = 0; index < 32; ++index) {
        if (sequencer->midi_headers[index] == header)
            break;
    }
    if (index == 32)
        return;

    sequencer->midi_headers[index] = 0;
    void* output = *reinterpret_cast<void**>(
        reinterpret_cast<unsigned char*>(sequencer) + 0x13c);
    MidiOutUnprepareHeaderAtRetail()(output, header, 0x40);
    if (header->lpData != 0) {
        asm_free_00452422(header->lpData);
        header->lpData = 0;
    }
    asm_free_00452422(header);
}

// The game runtime helper implements unsigned 64-bit division by a positive
// 32-bit tempo.  Keeping the division in 32-bit limbs avoids acquiring a
// compiler-private __aulldiv dependency in this source region.
static __forceinline unsigned __int64 DivideMidiTicksByTempo(
    unsigned __int64 numerator,
    unsigned int tempo) {
    const unsigned int numeratorLow = static_cast<unsigned int>(numerator);
    const unsigned int numeratorHigh = static_cast<unsigned int>(numerator >> 32);
    unsigned int quotientHigh = numeratorHigh / tempo;
    unsigned int remainder = numeratorHigh % tempo;
    unsigned int quotientLow = 0;
    int bit = 31;

    for (; bit >= 0; --bit) {
        const unsigned int carry = remainder >> 31;
        remainder = (remainder << 1) | ((numeratorLow >> bit) & 1);
        if (carry || remainder >= tempo) {
            remainder -= tempo;
            quotientLow |= 1u << bit;
        }
    }

    return (static_cast<unsigned __int64>(quotientHigh) << 32) | quotientLow;
}

static __forceinline unsigned __int64 MidiEventElapsedTicks(MidiSequencer* sequencer) {
    const unsigned int ticksPerQuarter =
        static_cast<unsigned int>(sequencer->ticks_per_quarter_note);
    const unsigned int ticksPerQuarterHigh =
        sequencer->ticks_per_quarter_note < 0 ? 0xffffffffu : 0;
    const unsigned __int64 scaledByDivision = Allmul_00456640(
        ticksPerQuarter,
        ticksPerQuarterHigh,
        static_cast<unsigned int>(sequencer->elapsed_timer_ticks),
        static_cast<unsigned int>(sequencer->elapsed_timer_ticks >> 32));
    const unsigned __int64 milliseconds = Allmul_00456640(
        static_cast<unsigned int>(scaledByDivision),
        static_cast<unsigned int>(scaledByDivision >> 32),
        1000,
        0);
    return DivideMidiTicksByTempo(
        milliseconds,
        static_cast<unsigned int>(sequencer->tempo_microseconds));
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
    if (status < 0x80) {
        status = track->running_status;
    } else {
        ++track->cursor;
    }

    const unsigned char channel = status & 0x0f;
    const unsigned char messageType = status & 0xf0;
    if (messageType == 0x80 || messageType == 0x90 ||
        messageType == 0xa0 || messageType == 0xb0 ||
        messageType == 0xe0) {
        data1 = *track->cursor++;
        data2 = *track->cursor++;
    } else if (messageType == 0xc0 || messageType == 0xd0) {
        data1 = *track->cursor++;
    } else if (messageType == 0xf0) {
        if (status == 0xf0) {
            const int headerIndex = sequencer->midi_header_index;
            if (sequencer->midi_headers[headerIndex] != 0)
                ReleaseQueuedMidiHeader(sequencer, sequencer->midi_headers[headerIndex]);

            midihdr_tag* header = static_cast<midihdr_tag*>(asm_malloc_00452706(0x40));
            sequencer->midi_headers[headerIndex] = header;
            const int sysexLength = static_cast<int>(ReadMidiEventValue(track->cursor));

            unsigned int* headerWords = reinterpret_cast<unsigned int*>(header);
            int word;
            for (word = 0; word < 16; ++word)
                headerWords[word] = 0;

            header->lpData = static_cast<char*>(asm_malloc_00452706(
                static_cast<unsigned int>(sysexLength) + 1));
            header->lpData[0] = static_cast<char>(0xf0);
            header->dwFlags = 0;
            header->dwBufferLength = static_cast<unsigned int>(sysexLength) + 1;
            int byteIndex;
            for (byteIndex = 0; byteIndex < sysexLength; ++byteIndex)
                header->lpData[byteIndex + 1] = static_cast<char>(*track->cursor++);

            void* output = *reinterpret_cast<void**>(
                reinterpret_cast<unsigned char*>(sequencer) + 0x13c);
            if (output != 0 &&
                (MidiOutPrepareHeaderAtRetail()(output, header, 0x40) != 0 ||
                 MidiOutLongMsgAtRetail()(output, header, 0x40) != 0)) {
                if (header->lpData != 0) {
                    asm_free_00452422(header->lpData);
                    header->lpData = 0;
                }
                asm_free_00452422(header);
                sequencer->midi_headers[headerIndex] = 0;
            }

            sequencer->midi_header_index = (headerIndex + 1) & 0x1f;
        } else if (status == 0xff) {
            const unsigned char metaType = *track->cursor++;
            const int metaLength = static_cast<int>(ReadMidiEventValue(track->cursor));
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
                        sequencer->tempo_microseconds * 0x101 + *track->cursor++;
                }
            } else {
                track->cursor += metaLength;
            }
        }
    }

    unsigned char* state = reinterpret_cast<unsigned char*>(sequencer);
    unsigned char* channelState = state + 0x154 + channel * 0x17;
    if (messageType == 0x90 && data2 != 0) {
        const signed char transpose = *reinterpret_cast<signed char*>(state + 0x2c4);
        const unsigned char note = static_cast<unsigned char>(data1 + transpose);
        unsigned char* noteBits = channelState + (note >> 3);
        *noteBits |= static_cast<unsigned char>(1u << (note & 7));
    } else if (messageType == 0x80 || messageType == 0x90) {
        const signed char transpose = *reinterpret_cast<signed char*>(state + 0x2c4);
        const unsigned char note = static_cast<unsigned char>(data1 + transpose);
        unsigned char* noteBits = channelState + (note >> 3);
        *noteBits &= static_cast<unsigned char>(~(1u << (note & 7)));
    } else if (messageType == 0xb0) {
        switch (data1) {
        case 0:
            channelState[0x11] = data2;
            break;
        case 2: {
            int index;
            for (index = 0; index < sequencer->track_count; ++index) {
                sequencer->tracks[index].loop_cursor = sequencer->tracks[index].cursor;
                sequencer->tracks[index].saved_loop_time =
                    sequencer->tracks[index].next_event_time;
            }
            unsigned int* savedClock = reinterpret_cast<unsigned int*>(state + 0x2ec);
            const unsigned int* clock = reinterpret_cast<const unsigned int*>(state + 0x124);
            for (index = 0; index < 5; ++index)
                savedClock[index] = clock[index];
            break;
        }
        case 4: {
            int index;
            for (index = 0; index < sequencer->track_count; ++index) {
                sequencer->tracks[index].cursor = sequencer->tracks[index].loop_cursor;
                sequencer->tracks[index].next_event_time =
                    sequencer->tracks[index].saved_loop_time;
            }
            unsigned int* clock = reinterpret_cast<unsigned int*>(state + 0x124);
            const unsigned int* savedClock = reinterpret_cast<const unsigned int*>(state + 0x2ec);
            for (index = 0; index < 5; ++index)
                clock[index] = savedClock[index];
            break;
        }
        case 7: {
            channelState[0x15] = data2;
            const float adjustedVolume = static_cast<float>(data2) * sequencer->fade_volume;
            int volume = static_cast<int>(adjustedVolume);
            if (volume < 0) {
                channelState[0x16] = 0;
                data2 = 0;
            } else {
                if (volume > 0x7f)
                    volume = 0x7f;
                channelState[0x16] = static_cast<unsigned char>(volume);
                data2 = static_cast<unsigned char>(volume);
            }
            break;
        }
        case 10:
            channelState[0x12] = data2;
            break;
        case 0x5b:
            channelState[0x13] = data2;
            break;
        case 0x5d:
            channelState[0x14] = data2;
            break;
        }
    } else if (messageType == 0xc0) {
        channelState[0x10] = data1;
    }

    void* output = *reinterpret_cast<void**>(state + 0x13c);
    if (status < 0xf0 && output != 0) {
        const unsigned int message =
            static_cast<unsigned int>(status) |
            (static_cast<unsigned int>(data1) << 8) |
            (static_cast<unsigned int>(data2) << 16);
        MidiOutShortMsgAtRetail()(output, message);
    }

    track->running_status = status;
    const unsigned int delta = ReadMidiEventValue(track->cursor);
    track->next_event_time = static_cast<int>(
        static_cast<unsigned int>(track->next_event_time) + delta);
}
