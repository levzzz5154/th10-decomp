// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_408820.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00408820** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Offset();
    }
    return total;
}
#pragma code_seg()
