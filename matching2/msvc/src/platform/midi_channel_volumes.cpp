// 0x0043B7A0: scale and adjust the volume of all sixteen MIDI channels.
// Native LTCG retains the receiver in EDI and the adjustment on the stack.
#include <stddef.h>

struct MidiVolumeChannel {
    unsigned char opaque[0x15];
    unsigned char requested_volume;
    unsigned char applied_volume;
};

// Partial view of the channel-volume fields; the remaining sequencer storage
// is opaque. Channel records begin at +0x154 and have a 0x17-byte stride.
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

    __declspec(noinline) void ApplyChannelVolumes(int adjustment);
};


typedef char MidiVolumeChannel_size[sizeof(MidiVolumeChannel) == 0x17 ? 1 : -1];
typedef char MidiVolume_output_offset[offsetof(MidiVolumeState, output) == 0x13c ? 1 : -1];
typedef char MidiVolume_channels_offset[offsetof(MidiVolumeState, channels) == 0x154 ? 1 : -1];
typedef char MidiVolume_fade_offset[offsetof(MidiVolumeState, fade_volume) == 0x2c8 ? 1 : -1];
typedef char MidiVolume_suppress_offset[offsetof(MidiVolumeState, suppress_volume_updates) == 0x2d4 ? 1 : -1];

typedef unsigned int (__stdcall *MidiOutShortMsgCall)(void*, unsigned int);
extern "C" MidiOutShortMsgCall IatTickMidiOutShortMsg;
#pragma code_seg(".text$01volume")
// Native entry: receiver in EDI, adjustment on the stack, RET 4.
void MidiVolumeState::ApplyChannelVolumes(int adjustment) {
    MidiVolumeState& state = *this;
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
