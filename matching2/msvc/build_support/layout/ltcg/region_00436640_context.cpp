// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_436640.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object9** items, int count) {
    while (count--) {
        (*items++)->Construct();
    }
    return 0;
}
#pragma code_seg()
