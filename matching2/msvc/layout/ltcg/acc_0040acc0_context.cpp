// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040acc0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040acc0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadMasked(count);
    }
    return total;
}
#pragma code_seg()
