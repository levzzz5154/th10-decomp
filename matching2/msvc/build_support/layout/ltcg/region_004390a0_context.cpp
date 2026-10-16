// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4390a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object22** items, int count, unsigned int flags) {
    while (count--) {
        (*items++)->Destroy(flags);
    }
    return 0;
}
#pragma code_seg()
