// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_40c920.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040c920** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Accumulate(count);
    }
    return total;
}
#pragma code_seg()
