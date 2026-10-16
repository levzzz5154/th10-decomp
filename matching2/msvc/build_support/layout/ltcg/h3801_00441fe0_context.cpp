// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_441fe0.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_00441fe0(ObjectAccessor_00441fe0** items, int count, int value) {
    while (count--) {
        ObjectAccessor_00441fe0* object = *items++;
        object->StoreValue(value);
        object->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
