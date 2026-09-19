// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043c930.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043c930** items, int count) {
    while (count--) {
        (*items++)->Open();
    }
    return 0;
}
#pragma code_seg()
