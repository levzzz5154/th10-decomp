// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00442170_00442170.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3901CompilerContext_00442170(
        ObjectAccessor_00442170** items, int count, int value) {
    while (count--) {
        ObjectAccessor_00442170* object = *items++;
        object->StoreValue(value);
        object->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
