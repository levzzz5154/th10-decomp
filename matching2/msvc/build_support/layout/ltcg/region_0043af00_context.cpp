// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43af00.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object29** items, int count, void* value) {
    while (count--) {
        (*items++)->Reset(value);
    }
    return 0;
}
#pragma code_seg()
