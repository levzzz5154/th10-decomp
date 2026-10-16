// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43a540.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object26** items, int count, void* header) {
    int total = 0;
    while (count--) {
        total += (*items++)->SendLong(header);
    }
    return total;
}
#pragma code_seg()
