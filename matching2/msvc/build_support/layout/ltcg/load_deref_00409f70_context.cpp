// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_409f70.cpp"

#pragma code_seg(".text$03context")
int __stdcall LoadCompilerContext(LoadDeref** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Load();
    }
    return total;
}
#pragma code_seg()
