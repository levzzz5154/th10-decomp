// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43a4a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object24** items, int count) {
    while (count--) {
        (*items++)->Close();
    }
    return 0;
}
#pragma code_seg()
