// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00405580_00405580.cpp"

extern "C" GameState* data_004776f4;

#pragma code_seg(".text$03context")
int __stdcall GameStateField3788GetterCompilerContext(int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += GameState_GetField3788(data_004776f4);
    }
    return total;
}
#pragma code_seg()
