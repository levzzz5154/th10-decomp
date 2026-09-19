// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00417630.cpp"
#pragma code_seg(".text$03context")
char* __stdcall OffsetContext_00417630(ObjectAccessor_00417630** items, int count) {
    char* last = 0;
    while (count--) {
        last = Offset_00417630(*items++);
    }
    return last;
}
#pragma code_seg()
