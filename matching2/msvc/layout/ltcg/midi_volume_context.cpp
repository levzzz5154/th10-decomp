// Compiler context; never selected as game code.
#include "../../src/platform/midi_channel_volumes.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall MidiVolumeContext(MidiVolumeState* sequence, int* adjustments, int count) {
    for (int index = 0; index < count; ++index)
        sequence->ApplyChannelVolumes(adjustments[index]);
    return count;
}
#pragma code_seg()
