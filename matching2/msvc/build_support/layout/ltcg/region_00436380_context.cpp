// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_436380.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object7** items, int count) {
    while (count--) {
        (*items++)->Init();
    }
    return 0;
}
#pragma code_seg()
