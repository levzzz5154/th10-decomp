// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00417650.cpp"
#pragma code_seg(".text$03context")
char* __stdcall OffsetContext_00417650(ObjectAccessor_00417650** items, int count) {
    char* last = 0;
    while (count--) {
        last = Offset_00417650(*items++);
    }
    return last;
}
#pragma code_seg()
