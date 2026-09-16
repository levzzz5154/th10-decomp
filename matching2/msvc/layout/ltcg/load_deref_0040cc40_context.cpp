// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040cc40_0040cc40.cpp"

#pragma code_seg(".text$03context")
int __stdcall LoadCompilerContext(LoadDeref_0040cc40** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Load();
    }
    return total;
}
#pragma code_seg()
