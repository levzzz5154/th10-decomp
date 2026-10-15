// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_004367f0_004367f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_004367f0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
