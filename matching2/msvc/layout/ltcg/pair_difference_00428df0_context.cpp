// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00428df0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall PairDifferenceCompilerContext_00428df0(PairDifference_00428df0** items, int count) {
    int result = 0;
    while (count-- != 0) result += PairDifference_00428df0_IsDifferent(*items++);
    return result;
}
#pragma code_seg()
