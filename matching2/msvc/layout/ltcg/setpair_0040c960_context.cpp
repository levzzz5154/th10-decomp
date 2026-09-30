// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0040c960_0040c960.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Pair_0040c960** items, int count, float a, float b) {
    while (count--) (*items++)->SetPair(a, b);
    return 0;
}
#pragma code_seg()
