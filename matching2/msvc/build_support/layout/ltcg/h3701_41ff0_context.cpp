// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00441ff0_00441ff0.cpp"

#pragma code_seg(".text$03ctx")
int __stdcall H3701F10Context(H3701F10** items, unsigned int** destinations, int count) {
    while (count--) {
        (*items++)->Copy(*destinations++);
    }
    return 0;
}
#pragma code_seg()
