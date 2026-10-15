// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0043a1b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043a1b0** items, int count) {
    while (count--) {
        (*items++)->Activate();
    }
    return 0;
}
#pragma code_seg()
