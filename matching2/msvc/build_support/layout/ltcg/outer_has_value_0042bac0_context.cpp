// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_42bac0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall OuterHasValueContext_0042bac0(Outer2** items, int count) {
    int found = 0;
    while (count--) {
        found += (*items++)->HasValue();
    }
    return found;
}
#pragma code_seg()
