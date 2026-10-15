// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/unassigned_0043a4c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(MidiOutput_0043a4c0** m, unsigned int* d, int n, void*** escape) {
    int r = 0;
    *escape = &data_00491c70;
    for (int i = 0; i < n; ++i) r += OpenMidiOutput_0043a4c0(m[i], d[i]);
    return r;
}
#pragma code_seg()
