// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_438940.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object16** items, int count) {
    while (count--) {
        (*items++)->Init();
    }
    return 0;
}
#pragma code_seg()
