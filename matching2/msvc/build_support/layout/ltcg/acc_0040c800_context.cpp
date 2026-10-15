// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0040c800.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040c800** items, int count) {
    while (count--) {
        (*items++)->Clear();
    }
    return 0;
}
#pragma code_seg()
