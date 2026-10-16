// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_405000.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00405000** items, Vec35* src) {
    int n = 4;
    while (n--) (*items++)->CopyFrom(src);
    return 0;
}
#pragma code_seg()
