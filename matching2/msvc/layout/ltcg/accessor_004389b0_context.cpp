// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004389b0_004389b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_004389b0** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
