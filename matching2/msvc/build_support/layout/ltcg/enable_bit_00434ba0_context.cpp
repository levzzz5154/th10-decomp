// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_434ba0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FlagWord** items, unsigned int* values, int count) {
    while (count--) (*items++)->SetEnabled(*values++);
    return 0;
}
#pragma code_seg()
