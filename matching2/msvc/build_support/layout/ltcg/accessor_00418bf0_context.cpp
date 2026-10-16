// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_418bf0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00418bf0** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
