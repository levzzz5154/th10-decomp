// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_439060.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object21** items, int count, unsigned int flags) {
    while (count--) {
        (*items++)->Destroy(flags);
    }
    return 0;
}
#pragma code_seg()
