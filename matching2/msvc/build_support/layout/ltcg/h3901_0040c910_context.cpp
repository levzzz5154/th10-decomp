// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_40c910.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3901CompilerContext_0040c910(
        ObjectAccessor_0040c910** items, int count, int value) {
    while (count--) {
        ObjectAccessor_0040c910* object = *items++;
        object->StoreValue(value);
        object->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
