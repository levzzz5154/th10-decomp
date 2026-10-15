// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_004245a0_004245a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_004245a0** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
