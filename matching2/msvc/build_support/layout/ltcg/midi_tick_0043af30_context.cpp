// Compiler context only; never selected as recovered game code.
#include "../../../src/core/midilib/midi_tick.cpp"

// An escaping method pointer keeps Tick's public ECX receiver boundary. It is
// read-only after construction, so it lives in .rdata and this entry is the
// link's only reference to it.
typedef void (MidiTickState::*MidiTickMethod)();
#pragma data_seg(".rdata$07entry")
MidiTickMethod volatile MidiTickEntry = &MidiTickState::Tick;
#pragma data_seg()
#pragma code_seg(".text$07context")
extern "C" int __stdcall MidiTickContext(MidiTickState** sequences, int* adjustments, int count) {
    for (int index = 0; index < count; ++index) {
        (sequences[index]->*MidiTickEntry)();
        sequences[index]->ApplyChannelVolumes(adjustments[index]);
    }
    return count;
}
#pragma code_seg()
