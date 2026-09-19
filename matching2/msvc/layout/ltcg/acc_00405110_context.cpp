// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00405110.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00405110** items, Vec3_00405110* src) {
    int n = 4;
    while (n--) (*items++)->CopyFrom(src);
    return 0;
}
#pragma code_seg()
