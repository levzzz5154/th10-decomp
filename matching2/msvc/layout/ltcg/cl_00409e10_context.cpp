// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00409e10.cpp"

#pragma code_seg(".text$03context")
int __stdcall EvaluateContext_00409e10(Vector_00409e10** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += (*items++)->Evaluate();
    }
    return total;
}
#pragma code_seg()
