// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004369c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_004369c0** items, int count) {
    while (count--) {
        (*items++)->Release();
    }
    return 0;
}
#pragma code_seg()
