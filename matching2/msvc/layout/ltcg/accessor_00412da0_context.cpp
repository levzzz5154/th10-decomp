// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00412da0_00412da0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00412da0** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
