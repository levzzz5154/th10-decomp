// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_40c5f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResolveContext_0040c5f0(OperandSource** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += (*items++)->Resolve(i);
    }
    return total;
}
#pragma code_seg()
