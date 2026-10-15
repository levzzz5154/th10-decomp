// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0040dc70.cpp"

#pragma code_seg(".text$03context")
int __stdcall RunContext_0040dc70(Outer_0040dc70** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += (*items++)->Run();
    }
    return total;
}
#pragma code_seg()
