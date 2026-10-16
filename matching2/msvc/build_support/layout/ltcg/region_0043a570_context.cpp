// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43a570.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object27** items, int count, unsigned int message) {
    int total = 0;
    while (count--) {
        total += (*items++)->Send(message);
    }
    return total;
}
#pragma code_seg()
