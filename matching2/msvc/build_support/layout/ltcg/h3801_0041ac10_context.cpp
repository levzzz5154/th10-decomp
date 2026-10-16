// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ac10.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_0041ac10(ObjectAccessor_0041ac10** items, int count, int value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
