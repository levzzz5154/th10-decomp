// The cluster entry translation unit: the MIDI event parser and a stand-in
// for its caller, the sequencer tick at 0x0043AF30. The parser only compiles
// like retail when it is an internal function with a visible direct caller.
// The stand-in is compiler context only, not recovered code.
#include "../../../../src/core/midilib/midi_event_parser.cpp"

#pragma code_seg(".text$50context")
extern "C" __declspec(noinline) int __stdcall MidiEventParserCaller(
    MidiSequencer* sequencer, int count) {
    for (int index = 0; index < count; ++index)
        ProcessMidiEvent_0043B110(sequencer, &sequencer->tracks[index]);
    sequencer->ResetTracks();
    return count;
}
#pragma code_seg()
