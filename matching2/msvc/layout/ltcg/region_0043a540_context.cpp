// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0043a540.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043a540** items, int count, void* header) {
    int total = 0;
    while (count--) {
        total += (*items++)->SendLong(header);
    }
    return total;
}
#pragma code_seg()
