// Compiler context only; never selected as recovered game code.
#include "../../../src/core/midilib/midi_reverse_dword_bytes_0043a700.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReverseDwordCompilerContext(unsigned int* values, int count) {
    while (count--) {
        *values = ReverseDwordBytes_0043a700(*values);
        ++values;
    }
    return 0;
}
#pragma code_seg()
