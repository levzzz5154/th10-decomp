// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040ae30_0040ae30.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040ae30** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
