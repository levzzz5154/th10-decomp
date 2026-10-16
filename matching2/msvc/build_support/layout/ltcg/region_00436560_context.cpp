// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_436560.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object8** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Abs();
    }
    return total;
}
#pragma code_seg()
