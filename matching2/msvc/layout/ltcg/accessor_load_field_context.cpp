// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_0040ac00_0040ac00.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorLoadCompilerContext(Object0040ac00** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Load();
    }
    return total;
}
#pragma code_seg()
