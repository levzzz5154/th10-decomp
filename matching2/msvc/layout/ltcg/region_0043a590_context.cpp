// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043a590.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043a590** items, int count,
        unsigned char status, unsigned char first, unsigned char second) {
    int total = 0;
    while (count--) {
        total += (*items++)->Send(status, first, second);
    }
    return total;
}
#pragma code_seg()
