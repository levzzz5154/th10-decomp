// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_401f40.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00401f40** items, int count) {
    while (count--) {
        (*items++)->Arm();
    }
    return 0;
}
#pragma code_seg()
