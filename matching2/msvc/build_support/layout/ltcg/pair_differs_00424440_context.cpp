// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_00424440.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(ValuePair_00424440** items, int count) {
    int sum = 0;
    while (count--) sum += (*items++)->Changed();
    return sum;
}
#pragma code_seg()
