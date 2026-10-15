// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0040cd80_0040cd80.cpp"

#pragma code_seg(".text$03ctx")
int __stdcall H3701CD80Fast2Context(int** items, int count, int index, int value) {
    while (count--) {
        H3701CD80_Fast2(index, *items++, value);
    }
    return 0;
}
#pragma code_seg()
