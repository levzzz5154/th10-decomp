// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_0040c590.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(IdHolder_0040c590** items, int count, int v) {
    int n = 0;
    while (count--) n += (*items++)->Matches(v);
    return n;
}
#pragma code_seg()
