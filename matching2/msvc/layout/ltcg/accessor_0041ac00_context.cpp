// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0041ac00_0041ac00.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0041ac00** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
