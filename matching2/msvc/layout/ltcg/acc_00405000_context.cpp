// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00405000.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00405000** items, Vec3_00405000* src) {
    int n = 4;
    while (n--) (*items++)->CopyFrom(src);
    return 0;
}
#pragma code_seg()
