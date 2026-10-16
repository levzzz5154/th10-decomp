// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41ff00.cpp"
#pragma code_seg(".text$03context")
int __stdcall MarkContext_0041ff00(ObjectAccessor_0041ff00** items, int count) {
    while (count--) {
        Mark2(*items++);
    }
    return 0;
}
#pragma code_seg()
