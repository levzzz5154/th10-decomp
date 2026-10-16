// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_43a5c0.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(char (*names)[32], unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) MidiOut_GetDeviceName(i, names[i]);
}
#pragma code_seg()
