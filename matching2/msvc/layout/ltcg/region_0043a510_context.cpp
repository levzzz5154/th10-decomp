// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0043a510.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043a510** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Close();
    }
    return total;
}
#pragma code_seg()
