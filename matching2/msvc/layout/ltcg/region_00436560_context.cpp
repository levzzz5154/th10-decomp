// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00436560.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00436560** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Abs();
    }
    return total;
}
#pragma code_seg()
