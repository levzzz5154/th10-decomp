// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0044c260.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall PolarUpdateContext_0044c260(PolarMotion_0044c260** items, int count) {
    while (count--) {
        PolarMotion_0044c260_Update(*items++);
    }
    return 0;
}
#pragma code_seg()
