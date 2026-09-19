// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004130c0.cpp"
#pragma code_seg(".text$03context")
char* __stdcall OffsetContext_004130c0(ObjectAccessor_004130c0** items, int count) {
    char* last = 0;
    while (count--) {
        last = Offset_004130c0(*items++);
    }
    return last;
}
#pragma code_seg()
