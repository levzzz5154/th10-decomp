// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00429b30.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall ReseedContext_00429b30(TimerRecord_00429b30** records,
                                                const int* values, int count) {
    int total = 0;
    while (count--) {
        total += Reseed_00429b30(*records++, *values++);
    }
    return total;
}
#pragma code_seg()
