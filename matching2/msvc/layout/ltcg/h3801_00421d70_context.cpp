// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421d70_00421d70.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_00421d70(WordStore_00421d70** items, int count, short value) {
    while (count--) {
        (*items++)->Store(value);
    }
    return 0;
}
#pragma code_seg()
