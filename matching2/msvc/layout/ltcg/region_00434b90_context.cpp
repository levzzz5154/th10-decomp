// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00434b90.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00434b90** items, int count, int value) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Plus(value);
    }
    return total;
}
#pragma code_seg()
