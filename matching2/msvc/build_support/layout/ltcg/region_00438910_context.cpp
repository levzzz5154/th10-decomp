// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_438910.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object15** items, int count) {
    while (count--) {
        (*items++)->Clear();
    }
    return 0;
}
#pragma code_seg()
