// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00402100.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00402100** items, int count) {
    while (count--) {
        (*items++)->ClearValue();
    }
    return 0;
}
#pragma code_seg()
