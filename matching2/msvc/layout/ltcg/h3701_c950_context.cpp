// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040c950_0040c950.cpp"

#pragma code_seg(".text$03ctx")
int __stdcall H3701C950Context(H3701C950** items, int count, int index, int value) {
    while (count--) {
        (*items++)->Store(index, value);
    }
    return 0;
}
#pragma code_seg()
