// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_004389e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall TailCompilerContext(Object_004389e0** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->Tail();
    }
    return total;
}
#pragma code_seg()
