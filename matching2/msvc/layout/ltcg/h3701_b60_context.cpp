// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00418b60_00418b60.cpp"

#pragma code_seg(".text$03ctx")
int __stdcall H3701B60Context(H3701B60** items, int count, short value) {
    while (count--) {
        (*items++)->Store(value);
    }
    return 0;
}
#pragma code_seg()
