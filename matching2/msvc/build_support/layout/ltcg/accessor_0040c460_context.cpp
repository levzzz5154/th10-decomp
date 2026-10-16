// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_40c460.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_0040c460** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
