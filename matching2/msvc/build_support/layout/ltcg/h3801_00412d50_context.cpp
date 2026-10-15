// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00412d50_00412d50.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_00412d50(StoreResult** items, int count, int value) {
    while (count--) {
        StoreResult* object = *items++;
        object->Store(value);
        object->Store(value);
    }
    return 0;
}
#pragma code_seg()
