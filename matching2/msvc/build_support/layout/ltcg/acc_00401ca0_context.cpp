// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_401ca0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00401ca0** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total != 0.0f;
}
#pragma code_seg()
