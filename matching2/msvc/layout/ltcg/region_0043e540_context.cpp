// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043e540.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043e540** items, int count, int index) {
    while (count--) {
        (*items++)->Release(index);
    }
    return 0;
}
#pragma code_seg()
