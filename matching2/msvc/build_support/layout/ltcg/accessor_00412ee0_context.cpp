// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_412ee0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00412ee0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
