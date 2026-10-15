// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00404410_00404410.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00404410CompilerContext(FUN_00404410_State** states, int count) {
    FUN_00404410_State** cursor = states;
    while (count--) {
        FUN_00404410_State* state = *cursor++;
        state->SetFlag();
        state->SetFlag();
    }
    return 0;
}
#pragma code_seg()
