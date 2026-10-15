// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0043cbf0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043cbf0** items, int count, unsigned int value) {
    while (count--) {
        (*items++)->Start(value);
    }
    return 0;
}
#pragma code_seg()
