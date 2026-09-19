// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043a4a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043a4a0** items, int count) {
    while (count--) {
        (*items++)->Close();
    }
    return 0;
}
#pragma code_seg()
