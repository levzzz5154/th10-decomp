// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0042a970_0042a970.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0042a970** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
