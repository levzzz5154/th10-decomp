// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040b2a0.cpp"
#pragma code_seg(".text$03context")
int __stdcall WorkerContext_0040b2a0(Worker_0040b2a0** items, int count) {
    int total = 0;
    while (count--) total += (*items++)->Update();
    return total;
}
#pragma code_seg()
