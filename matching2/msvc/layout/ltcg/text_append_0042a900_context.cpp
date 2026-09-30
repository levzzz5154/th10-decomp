// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_0042a900.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(LineBuffer_0042a900** items, char* chars, int count) {
    int full = 0;
    while (count--) full += (*items++)->Append(*chars++);
    return full;
}
#pragma code_seg()
