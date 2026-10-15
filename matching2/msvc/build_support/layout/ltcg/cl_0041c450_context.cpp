// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0041c450.cpp"
#pragma code_seg(".text$03context")
int __stdcall WalkContext_0041c450(ObjectAccessor_0041c450** items, int count) {
    int total = 0;
    while (count--) {
        total += Process_0041c450(*items++);
    }
    return total;
}
#pragma code_seg()
