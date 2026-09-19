// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040ce90.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040ce90** items, int count) {
    while (count--) {
        (*items++)->SetValue();
    }
    return 0;
}
#pragma code_seg()
