// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43aa30.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object28** items, int count, int index) {
    while (count--) {
        (*items++)->Release(index);
    }
    return 0;
}
#pragma code_seg()
