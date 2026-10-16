// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_40cd90.cpp"

#pragma code_seg(".text$03ctx")
int __stdcall H3701CD90Context(H3701CD90** items, int count, int index, int value) {
    while (count--) {
        (*items++)->Store(index, value);
    }
    return 0;
}
#pragma code_seg()
