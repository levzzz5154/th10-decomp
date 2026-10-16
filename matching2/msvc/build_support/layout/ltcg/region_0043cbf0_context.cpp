// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43cbf0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object32** items, int count, unsigned int value) {
    while (count--) {
        (*items++)->Start(value);
    }
    return 0;
}
#pragma code_seg()
