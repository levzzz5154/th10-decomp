// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00418ec0.cpp"
#pragma code_seg(".text$03context")
int __stdcall SetContext_00418ec0(ObjectAccessor_00418ec0** items, int count) {
    while (count--) {
        SetFlags_00418ec0(*items++);
    }
    return 0;
}
#pragma code_seg()
