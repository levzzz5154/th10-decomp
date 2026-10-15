// Compiler context only; this caller is not a recovered application function.
// The two live pointers establish the verified EDI and ESI internal arguments.
#include "../../../src/core/midilib/midi_tracks.cpp"

#pragma code_seg(".text$50context")
int __stdcall MidiCompilerContext(MidiSequencer* sequence,
                                 const unsigned char** cursor, int count) {
    int sum = 0;
    for (int index = 0; index < count; ++index) {
        sequence->ResetTracks();
        sum += ReadMidiVariableLength(*cursor);
    }
    return sum;
}
#pragma code_seg()
