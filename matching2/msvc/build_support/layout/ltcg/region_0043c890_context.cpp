// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43c890.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object31** items, int count, unsigned int flags) {
    while (count--) {
        (*items++)->Destroy(flags);
    }
    return 0;
}
#pragma code_seg()
