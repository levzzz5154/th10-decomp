// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0042c830_0042c830.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0042c830** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
