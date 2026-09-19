// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0042bac0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall OuterHasValueContext_0042bac0(Outer_0042bac0** items, int count) {
    int found = 0;
    while (count--) {
        found += (*items++)->HasValue();
    }
    return found;
}
#pragma code_seg()
