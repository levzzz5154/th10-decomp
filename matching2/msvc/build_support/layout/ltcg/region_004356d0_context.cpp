// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004356d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Path_004356d0** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->BaseName();
    }
    return total;
}
#pragma code_seg()
