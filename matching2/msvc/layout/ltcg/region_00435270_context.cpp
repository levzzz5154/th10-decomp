// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00435270.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00435270** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Next();
    }
    return total;
}
#pragma code_seg()
