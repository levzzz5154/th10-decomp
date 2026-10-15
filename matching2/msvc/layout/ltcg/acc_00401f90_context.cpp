// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00401f90.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00401f90** items, int count) {
    while (count--) {
        (*items++)->Set(count);
    }
    return 0;
}
#pragma code_seg()
