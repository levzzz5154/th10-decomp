// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00409dd0_00409dd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00409dd0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
