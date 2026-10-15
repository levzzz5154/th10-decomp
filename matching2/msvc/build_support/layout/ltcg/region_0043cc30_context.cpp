// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0043cc30.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043cc30** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Reset();
    }
    return total;
}
#pragma code_seg()
