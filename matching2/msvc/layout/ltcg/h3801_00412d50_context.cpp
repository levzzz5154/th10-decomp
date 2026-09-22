// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00412d50_00412d50.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_00412d50(StoreResult_00412d50** items, int count, int value) {
    while (count--) {
        StoreResult_00412d50* object = *items++;
        object->Store(value);
        object->Store(value);
    }
    return 0;
}
#pragma code_seg()
