// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00404f20.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00404f20** items, int count) {
    while (count--) {
        (*items++)->ClearValue();
    }
    return 0;
}
#pragma code_seg()
