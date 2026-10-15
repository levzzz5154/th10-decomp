// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00405580_00405580.cpp"

extern "C" GameState* g_card;

#pragma code_seg(".text$03context")
int __stdcall GameStateField3788GetterCompilerContext(int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += GameState_GetField3788(g_card);
    }
    return total;
}
#pragma code_seg()
