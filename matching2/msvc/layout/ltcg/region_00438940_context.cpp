// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00438940.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00438940** items, int count) {
    while (count--) {
        (*items++)->Init();
    }
    return 0;
}
#pragma code_seg()
