// Compiler context only.
#include "../../src/platform/midi_tick.cpp"
#include "midi_tick_reset.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall MidiTickContext(MidiTickState** sequence, int* adjustments, int count) {
    for (int index = 0; index < count; ++index) {
        sequence[index]->Tick();
        sequence[index]->ApplyChannelVolumes(adjustments[index]);
    }
    return count;
}
#pragma code_seg()
