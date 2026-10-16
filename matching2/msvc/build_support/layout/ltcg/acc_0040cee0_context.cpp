// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_40cee0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040cee0** items, Vec317* src) {
    int n = 4;
    while (n--) (*items++)->CopyFrom(src);
    return 0;
}
#pragma code_seg()
