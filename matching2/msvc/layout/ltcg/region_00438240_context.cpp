// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00438240.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00438240** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Data();
    }
    return total;
}
#pragma code_seg()
