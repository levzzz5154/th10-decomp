// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043bc10.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043bc10** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Tail();
    }
    return total;
}
#pragma code_seg()
