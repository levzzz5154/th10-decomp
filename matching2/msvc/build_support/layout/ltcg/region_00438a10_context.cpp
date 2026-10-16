// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_438a10.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object19** items, int count) {
    while (count--) {
        (*items++)->Release();
    }
    return 0;
}
#pragma code_seg()
