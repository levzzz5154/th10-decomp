// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00408ac0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00408ac0** items, int count) {
    while (count--) {
        (*items++)->Set();
    }
    return 0;
}
#pragma code_seg()
