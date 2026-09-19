// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00434ba0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00434ba0** items, int count, unsigned int mask) {
    while (count--) {
        (*items++)->Toggle(mask);
    }
    return 0;
}
#pragma code_seg()
