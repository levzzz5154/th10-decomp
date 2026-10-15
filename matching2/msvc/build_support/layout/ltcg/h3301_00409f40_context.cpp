// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00409f40_00409f40.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3301Context_00409f40(
        H3301Table_00409f40** tables, const int* indices, int count) {
    int total = 0;
    while (count--) {
        total += (*tables++)->GetValue(*indices++);
    }
    return total;
}
#pragma code_seg()
