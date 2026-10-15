// Compiler context only; this caller is not a recovered application function.
#include "../../../src/core/midilib/midi_file.cpp"

#pragma code_seg(".text$50context")
int __stdcall MidiFileCompilerContext(MidiSequencer* sequence, int slot, int count) {
    int sum = 0;
    for (int index = 0; index < count; ++index)
        sum += sequence->ParseLoadedFile(slot);
    return sum;
}
#pragma code_seg()
