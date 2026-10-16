// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_413120.cpp"
#pragma code_seg(".text$03context")
void __stdcall CopyContext_00413120(ObjectAccessor_00413120** items, Triple2** values, int count) {
    while (count--) {
        (*items++)->Assign(**values++);
    }
}
#pragma code_seg()
