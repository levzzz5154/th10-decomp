// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00401fb0_00401fb0.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00401fb0CompilerContext(FUN_00401fb0_State** states, int count) {
    FUN_00401fb0_State** cursor = states;
    while (count--) {
        FUN_00401fb0_State* state = *cursor++;
        state->StoreValue(count);
    }
    return 0;
}
#pragma code_seg()
