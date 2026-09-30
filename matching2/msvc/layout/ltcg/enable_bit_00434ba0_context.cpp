// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00434ba0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FlagWord_00434ba0** items, unsigned int* values, int count) {
    while (count--) (*items++)->SetEnabled(*values++);
    return 0;
}
#pragma code_seg()
