// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00439060.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_00439060** items, int count, unsigned int flags) {
    while (count--) {
        (*items++)->Destroy(flags);
    }
    return 0;
}
#pragma code_seg()
