// Equivalent MIDI tick recovery: one reviewed address-calculation difference.
// See reference/recovery_notes/midi_tick_equivalent_2026_10_05.md.
// Volume, ResetTracks, and the caller below establish compiler context only;
// emitted Tick calls are bound to the existing production helper addresses.
#include "th10/platform/midi_sequencer.hpp"

struct MidiVolumeChannel {
    unsigned char opaque[0x15];
    unsigned char requested_volume;
    unsigned char applied_volume;
};

// An overlay for fields still opaque in the canonical MidiSequencer header.
// This does not replace that type or claim that the opaque bytes are recovered.
struct MidiVolumeState {
    unsigned char opaque_000[0x13c];
    void* output;
    unsigned char opaque_140[0x14];
    MidiVolumeChannel channels[16];
    unsigned char opaque_2c4[4];
    float fade_volume;
    int fade_step;
    unsigned char opaque_2d0[4];
    int suppress_volume_updates;
};

struct MidiFadeState {
    unsigned char opaque[0x2e4];
    int fade_duration;
    int fade_position;
};

struct MidiTickState {
    // MidiSequencer has tail padding for its 64-bit members. Appending fields
    // to it would incorrectly place the duration at +0x2e8, rather than +0x2e4.
    union {
        MidiSequencer sequencer;
        MidiFadeState fade;
    };

    __declspec(noinline) void Tick();
    __declspec(noinline) void ApplyChannelVolumes(int adjustment);
};

typedef char MidiVolumeChannel_size[sizeof(MidiVolumeChannel) == 0x17 ? 1 : -1];
typedef char MidiVolume_output_offset[offsetof(MidiVolumeState, output) == 0x13c ? 1 : -1];
typedef char MidiVolume_channels_offset[offsetof(MidiVolumeState, channels) == 0x154 ? 1 : -1];
typedef char MidiVolume_requested_offset[offsetof(MidiVolumeChannel, requested_volume) == 0x15 ? 1 : -1];
typedef char MidiVolume_fade_offset[offsetof(MidiVolumeState, fade_volume) == 0x2c8 ? 1 : -1];
typedef char MidiVolume_step_offset[offsetof(MidiVolumeState, fade_step) == 0x2cc ? 1 : -1];
typedef char MidiVolume_suppress_offset[offsetof(MidiVolumeState, suppress_volume_updates) == 0x2d4 ? 1 : -1];
typedef char MidiTick_fade_base[offsetof(MidiTickState, fade) == 0 ? 1 : -1];
typedef char MidiTick_duration_offset[offsetof(MidiFadeState, fade_duration) == 0x2e4 ? 1 : -1];
typedef char MidiTick_position_offset[offsetof(MidiFadeState, fade_position) == 0x2e8 ? 1 : -1];

typedef unsigned int (__stdcall *MidiOutShortMsgCall)(void*, unsigned int);
extern "C" MidiOutShortMsgCall IatTickMidiOutShortMsg;

// The maintained parser still owns this address as assembly. Its retail
// boundary is two stack arguments, RET 8. A future probe must retain that ABI.
extern "C" __declspec(noinline) void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer*, MidiTrack*);

static __forceinline unsigned __int64 EventTime(const MidiSequencer& sequencer) {
    // CDQ sign-extends both signed 32-bit parameters before unsigned 64-bit
    // multiply/divide. Do not replace the denominator with a uint32 cast.
    return sequencer.event_tick_base +
        (static_cast<unsigned __int64>(static_cast<__int64>(sequencer.ticks_per_quarter_note)) *
         sequencer.elapsed_timer_ticks * 1000) /
        static_cast<unsigned __int64>(static_cast<__int64>(sequencer.tempo_microseconds));
}

// Callback processing can replace the track table; reload at each decision.
static __forceinline MidiTrack* CurrentTrack(MidiSequencer& sequence, int index) {
    return reinterpret_cast<MidiTrack* volatile&>(sequence.tracks) + index;
}

#pragma code_seg(".text$03tick")
// 0x0043AF30, complete retail contribution: 473 bytes. Entry receiver ECX.
void MidiTickState::Tick() {
    int any_active = 0;
    unsigned __int64 event_time = EventTime(sequencer);
    MidiVolumeState& volume = *reinterpret_cast<MidiVolumeState*>(this);
    if (sequencer.fade_active) {
        if (fade.fade_position < fade.fade_duration) {
            // Retail FST stores the float but retains the x87 result for the first
            // conversion. The post-call conversion explicitly reloads that float.
            float level = 1.0f - static_cast<float>(fade.fade_position) / fade.fade_duration;
            sequencer.fade_volume = level;
            int step = static_cast<int>(static_cast<__int64>(level * 128.0f));
            if (step != volume.fade_step)
                ApplyChannelVolumes(0);
            volume.fade_step = static_cast<int>(
                static_cast<__int64>(sequencer.fade_volume * 128.0f));
            ++fade.fade_position;
        } else {
            sequencer.fade_volume = 0.0f;
            return;
        }
    }

    for (int index = 0; index < sequencer.track_count; ++index) {
        if (!CurrentTrack(sequencer, index)->active)
            continue;
        any_active = 1;
        do {
            MidiTrack* track = CurrentTrack(sequencer, index);
            // Retail CDQ followed by unsigned high/low compares: negative
            // event times become large unsigned values, rather than due events.
            if (static_cast<unsigned __int64>(
                    static_cast<__int64>(track->next_event_time)) > event_time)
                break;
            ProcessMidiEvent_0043B110(&sequencer, track);
            event_time = EventTime(sequencer);
        } while (CurrentTrack(sequencer, index)->active);
    }
    ++sequencer.elapsed_timer_ticks;
    if (!any_active)
        sequencer.ResetTracks();
}


#pragma code_seg(".text$05volume")
// Native entry: receiver in EDI, adjustment on the stack, RET 4.
void MidiTickState::ApplyChannelVolumes(int adjustment) {
    MidiVolumeState& state = *reinterpret_cast<MidiVolumeState*>(this);
    if (state.suppress_volume_updates)
        return;

    // The message has three initialized bytes. Native MSVC reuses the incoming
    // argument slot, so its untouched fourth byte retains the argument high byte.
    unsigned int message;
    unsigned char* message_bytes = reinterpret_cast<unsigned char*>(&message);
    for (int channel = 0; channel < 16; ++channel) {
        const unsigned int status = static_cast<unsigned char>(channel + 0xb0);
        int value = static_cast<int>(static_cast<__int64>(
            static_cast<float>(state.channels[channel].requested_volume) * state.fade_volume));
        // The retail ADD wraps at 32 bits before its signed clamp.
        value = static_cast<int>(static_cast<unsigned int>(value) +
                                 static_cast<unsigned int>(adjustment));
        if (value < 0)
            value = 0;
        else if (value > 127)
            value = 127;
        if (state.output) {
            message_bytes[0] = static_cast<unsigned char>(status);
            message_bytes[2] = static_cast<unsigned char>(value);
            message_bytes[1] = 7;
            IatTickMidiOutShortMsg(state.output, message);
        }
    }
}
#pragma code_seg()

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

// 0x0043ACE0: rewind the tracks and read their initial event delays.
#pragma code_seg(".text$01reset")
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

// An escaping method pointer keeps Tick's public ECX receiver boundary.
typedef void (MidiTickState::*MidiTickMethod)();
MidiTickMethod volatile MidiTickEntry = &MidiTickState::Tick;
#pragma code_seg(".text$07context")
extern "C" int __stdcall MidiTickContext(MidiTickState** sequences, int* adjustments, int count) {
    for (int index = 0; index < count; ++index) {
        (sequences[index]->*MidiTickEntry)();
        sequences[index]->ApplyChannelVolumes(adjustments[index]);
    }
    return count;
}
