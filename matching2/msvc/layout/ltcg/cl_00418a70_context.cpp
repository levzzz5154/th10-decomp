// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418a70.cpp"
#pragma code_seg(".text$03context")
int __stdcall ClearContext_00418a70(ObjectAccessor_00418a70** items, int count) {
    while (count--) {
        ClearFlags_00418a70(*items++);
    }
    return 0;
}
#pragma code_seg()
