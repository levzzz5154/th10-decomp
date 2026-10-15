// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_0043a590.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(MidiOutput_0043a590** m, unsigned char* d, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += SendShortMessage(m[i], d[i], d[i + 1], d[i + 2]);
    return r;
}
#pragma code_seg()
