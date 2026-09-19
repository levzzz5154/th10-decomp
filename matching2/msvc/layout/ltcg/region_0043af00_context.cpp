// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043af00.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043af00** items, int count, void* value) {
    while (count--) {
        (*items++)->Reset(value);
    }
    return 0;
}
#pragma code_seg()
