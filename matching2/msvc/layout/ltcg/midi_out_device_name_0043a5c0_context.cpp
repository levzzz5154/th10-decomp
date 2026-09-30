// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0043a5c0_0043a5c0.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(char (*names)[32], unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) MidiOut_GetDeviceName_0043a5c0(i, names[i]);
}
#pragma code_seg()
