// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0043e530_0043e530.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0043e530** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
