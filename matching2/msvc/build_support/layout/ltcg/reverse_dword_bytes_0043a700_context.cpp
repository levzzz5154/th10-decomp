// Compiler context only; never selected as recovered game code.
#include "../../../src/core/midilib/midi_reverse_dword_bytes.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReverseDwordCompilerContext(unsigned int* values, int count) {
    while (count--) {
        *values = ReverseDwordBytes(*values);
        ++values;
    }
    return 0;
}
#pragma code_seg()
