// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00422200.cpp"
#pragma code_seg(".text$03context")
int __stdcall SetContext_00422200(ObjectAccessor_00422200** items, int count) {
    while (count--) {
        SetFlags_00422200(*items++);
    }
    return 0;
}
#pragma code_seg()
