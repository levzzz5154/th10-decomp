// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_405020.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00405020** items, Vec36* src) {
    int n = 4;
    while (n--) (*items++)->CopyFrom(src);
    return 0;
}
#pragma code_seg()
